#include "Quadtree.h"
#include "../Physics/Physics.h"

#include <chrono>
#include <string>

Quadtree::Quadtree(int width, int height, int tile, QuadtreeType t, bool isStatic, bool drawing) :
	mapWidth(width), mapHeight(height), tileSize(tile), type(t),
	//boundingBox(SDL_Rect{ -1 * tile, -1 * tile, width * tile, height * tile }),
	cullingBoundingBox(Game::camera), cullingScaleOffset(0),
	entities(GameScene::manager.getEntities()),
	nodes(nullptr), nodeCount(0), eleNodeCount(0),
	returnObjects(nullptr), returnObjectsCount(0),
	drawingEnabled(drawing),
	dynamicNodeCount(0) {
	// make the bounds a power of two so tiles don't get split down the middle
	int x = -48;
	int y = -48;

	boundingBox = SDL_Rect{ x, y, 2048, 2048 };

	// allocate memory
	nodes = new QuadtreeNode*[NODES_BUFFER_SIZE];

	for (int i = 0; i < NODES_BUFFER_SIZE; ++i) {
		nodes[i] = new QuadtreeNode{ -1, -1, -1, SDL_Rect{-1, -1, -1, -1}, leafType, 0, -1, -1, 0, false };
	}

	elements = new int[ELEMENT_BUFFER_SIZE];

	dynamicNodes = new DynamicQuadtreeNode*[ELEMENT_BUFFER_SIZE];

	QuadtreeNode* blankNode = new QuadtreeNode{ -1, -1, -1, SDL_Rect{-1, -1, -1, -1}, leafType, 0, -1, -1, 0, false };

	for (int i = 0; i < ELEMENT_BUFFER_SIZE; ++i) {
		dynamicNodes[i] = new DynamicQuadtreeNode{ -1, -1, -1, -1,  *blankNode };
	}

	if (type == collisionType) {
		returnObjects = new int[COLLISION_RETRIEVAL_BUFFER_SIZE];
	} else if (type == cullingType) {
		returnObjects = new int[CULLING_RETRIEVAL_BUFFER_SIZE];
	}

	this->buildTree();
}

Quadtree::~Quadtree() {
	delete[](nodes);
	delete[](dynamicNodes);
	delete(elements);
	delete(returnObjects);
}

void Quadtree::update() {
	if (keys[SDL_SCANCODE_8]) {
		drawingEnabled = !drawingEnabled;
	}

	if (keys[SDL_SCANCODE_7]) {
		this->buildTree();

	}

	//check for new entities and insert them
	CheckForNewEntities();

	//auto start = std::chrono::steady_clock::now();

	// update dynamic entities only
	this->updateTree();

	if (type == collisionType) {

		//auto end = std::chrono::steady_clock::now();

		//auto diff = end - start;

		//auto time = std::chrono::duration<double, std::milli>(diff).count();

		//std::cout << "     build time: " << time << std::endl;

		//auto start = std::chrono::steady_clock::now();

		this->checkCollision();

		//auto end = std::chrono::steady_clock::now();

		//auto diff = end - start;

		//auto time = std::chrono::duration<double, std::milli>(diff).count();

		//std::cout << "collision check: " << time << std::endl;

	} else if (type == cullingType) {
		cullingBoundingBox.x = Game::camera.x + (4 * -cullingScaleOffset);
		cullingBoundingBox.y = Game::camera.y + (2 * -cullingScaleOffset);

		cullingBoundingBox.w = (Game::camera.w) + ((2 * cullingScaleOffset) * 4);
		cullingBoundingBox.h = (Game::camera.h) + ((2 * cullingScaleOffset) * 2);

		this->cullEntities();

		if (keys[SDL_SCANCODE_0]) {
			cullingScaleOffset++;
		}

		if (keys[SDL_SCANCODE_9]) {
			cullingScaleOffset--;
		}
	}

	this->cleanup();
}

void Quadtree::draw() {
	if (drawingEnabled)
	{
		SDL_Color col;
		if (type == collisionType) {
			col = SDL_Color{ 0, 255, 255, 255 };
			for (int i = 0; i < nodeCount; ++i) {
				if (nodes[i]->draw) {
					TextureManager::DrawBounds(&nodes[i]->rect, col);
				}
			}

		} else if (type == cullingType) {
			//col = SDL_Color{ 255, 0, 255, 255 };

			//for (int i = 0; i < nodeCount; ++i) {
			//	TextureManager::DrawBounds(&nodesTest[i]->rect, col);
			//}

			col = SDL_Color{ 255, 255, 0, 255 };
			TextureManager::DrawBounds(&cullingBoundingBox, col);
		}
	}
}

void Quadtree::buildTree() {
	if (nodeCount > 0) {
		nodeCount = 0;
		eleNodeCount = 0;
		dynamicNodeCount = 0;
	}

	createNewNode(nodes[0], 0, 0, boundingBox);
	nodeCount++;

	if (type == collisionType) {
		for (int i = 0; i < entities.size(); ++i) {
			if (entities[i]->hasComponent<ColliderComponent>()) {
				this->insert(nodes[0], entities[i]->getComponent<ColliderComponent>().collider, i);
				entityHeadCount.set(i);
			}
		}
	} else if (type == cullingType) {
		for (int i = 0; i < entities.size(); ++i) {
			if (entities[i]->hasComponent<SpriteComponent>()) {
				this->insert(nodes[0], entities[i]->getComponent<SpriteComponent>().getDest(), i);
				entityHeadCount.set(i);
			}
		}
	}
}

void Quadtree::updateTree() {
	for (int i = 0; i < (dynamicNodeCount * ELEMENT_NODE_BUFFER_SIZE); i += ELEMENT_NODE_BUFFER_SIZE) {
		for (int j = i; j < (i + dynamicNodes[i]->pNode.dNodeCount); j++)
		{		
			DynamicQuadtreeNode*& dNode = dynamicNodes[j];

			// remove the entity from the tree

			// shift elements left starting at index of removed element
			for (int k = dNode->localIndex; k < dNode->pNode.count - 1; k++) {
				elements[dNode->eleIndex + k] = elements[dNode->eleIndex + k + 1];
			}
			dNode->pNode.count--;
		}
	}

	std::vector<int> dynamicEntities = std::vector<int>();

	// re insert all dynamic nodes back into the tree
	for (int i = 0; i < (dynamicNodeCount * ELEMENT_NODE_BUFFER_SIZE); i += ELEMENT_NODE_BUFFER_SIZE) {
		DynamicQuadtreeNode* dNode = nullptr;

		for (int j = i; j < (i + dynamicNodes[i]->pNode.dNodeCount); j++) {
			dNode = dynamicNodes[j];

			dynamicEntities.push_back(dNode->entIndex);
		}

		if (dNode != nullptr) {
			dNode->pNode.dNodeCount = 0;
		}
	}

	for (int entIndex : dynamicEntities) {
		if (type == collisionType) {
			SDL_Rect entRect = entities[entIndex]->getComponent<ColliderComponent>().collider;
			this->insert(nodes[0], entRect, entIndex);
		} else if (type == cullingType) {
			SDL_Rect entRect = entities[entIndex]->getComponent<SpriteComponent>().getDest();
			this->insert(nodes[0], entRect, entIndex);
		}
	}
}

void Quadtree::insert(QuadtreeNode* pnode, SDL_Rect entRect, int entIndex) {
	if (pnode->type == nodeType) {
		int index = getQuadrantIndex(pnode->rect, entRect);

		if (index != -1) {
			this->insert(nodes[pnode->firstChild + index], entRect, entIndex);
			return;
		}
	}

	if (pnode->eleIndex > -1) {
		elements[pnode->eleIndex + pnode->count] = entIndex;
	} else {
		int eleNodeIndex = eleNodeCount * ELEMENT_NODE_BUFFER_SIZE;
		elements[eleNodeIndex] = entIndex;
		pnode->eleIndex = eleNodeIndex;
		eleNodeCount++;
	}

	// check if entity is dynamic
	// if so, add to dynamic node list
	if (entities[entIndex]->isDynamic()) {
 		if (pnode->dNodeIndex > -1) {
			dynamicNodes[pnode->dNodeIndex + pnode->dNodeCount] = new DynamicQuadtreeNode{ pnode->dNodeIndex + pnode->dNodeCount, pnode->eleIndex, pnode->count, entIndex, *pnode };
		} else {
			int dNodeIndex = dynamicNodeCount * ELEMENT_NODE_BUFFER_SIZE;
			dynamicNodes[dNodeIndex] = new DynamicQuadtreeNode{ dNodeIndex, pnode->eleIndex, pnode->count, entIndex, *pnode };
			pnode->dNodeIndex = dNodeIndex;
			dynamicNodeCount++;
		}
		pnode->dNodeCount++;
	}

	pnode->count++;

	if (pnode->count > MAX_OBJECTS && pnode->depth < MAX_DEPTH) {
		if (pnode->type == leafType) {
			if (pnode->firstChild == -1)
			{
				int nextAvailableCell = static_cast<int>(nodeCount);
				this->split(nextAvailableCell, pnode->rect, pnode->depth);
				pnode->firstChild = nextAvailableCell;
			}

			pnode->type = nodeType;
		}

		if (pnode->dNodeCount > 0) {
			pnode->dNodeCount = 0;
		}

		int i = 0;
		while (i < pnode->count) {
			SDL_Rect entRect;
			if (type == collisionType) {
				entRect = entities[elements[pnode->eleIndex + i]]->getComponent<ColliderComponent>().collider;
			} else if (type == cullingType) {
				entRect = entities[elements[pnode->eleIndex + i]]->getComponent<SpriteComponent>().getDest();
			}

			int index = getQuadrantIndex(pnode->rect, entRect);
			if (index != -1) {
				int eIndex = elements[pnode->eleIndex + i];

				//  shift elements left starting at index of removed element
				for (int j = i; j < pnode->count - 1; j++) {
					elements[pnode->eleIndex + j] = elements[pnode->eleIndex + j + 1];
				}
				pnode->count--;

				this->insert(nodes[pnode->firstChild + index], entRect, eIndex);
			} else {
				int eIndex = elements[pnode->eleIndex + i];

				if (entities[eIndex]->isDynamic()) {
					if (pnode->dNodeIndex > -1) {
						dynamicNodes[pnode->dNodeIndex + pnode->dNodeCount] = new DynamicQuadtreeNode{ pnode->dNodeIndex + pnode->dNodeCount, pnode->eleIndex, i, eIndex, *pnode };
					} else {
						int dNodeIndex = dynamicNodeCount * ELEMENT_NODE_BUFFER_SIZE;
						dynamicNodes[dNodeIndex] = new DynamicQuadtreeNode{ dNodeIndex, pnode->eleIndex, i, eIndex, *pnode };
						pnode->dNodeIndex = dNodeIndex;
						dynamicNodeCount++;
					}

					pnode->dNodeCount++;
				}

				i++;
			}
		}
	}
}

void Quadtree::cleanup() {
	std::vector<int> nodesToProcess = std::vector<int>();

	if (nodes[0]->type == QuadtreeNodeType::nodeType) {
		nodesToProcess.push_back(0);
	}

	while (nodesToProcess.size() > 0) {
		const int nodeIndex = nodesToProcess.back();
		nodesToProcess.pop_back();
		QuadtreeNode*& node = nodes[nodeIndex];

		int emptyLeafCount = 0;
		for (int i = 0; i < 4; ++i) {
			const int childIndex = node->firstChild + i;
			QuadtreeNode*& childNode = nodes[childIndex];

			if (childNode->type == QuadtreeNodeType::leafType && childNode->count == 0)
				++emptyLeafCount;
			else if(childNode->type == QuadtreeNodeType::nodeType)
				nodesToProcess.push_back(childIndex);
		}

		if (emptyLeafCount == 4) {
			for (int i = 0; i < 4; ++i) {
				const int childIndex = node->firstChild + i;
				QuadtreeNode*& childNode = nodes[childIndex];
				childNode->draw = false;
			}

			node->type = QuadtreeNodeType::leafType;
		}
	}
}


void Quadtree::retrieveAll(QuadtreeNode* pNode, SDL_Rect entRect) {
	IndexBitset indices = getAllQuadrantIndices(pNode->rect, entRect);

	for (int i = 0; i < 4; i++) {
		if (indices[i]) {
			if (nodes[pNode->index]->type == nodeType && nodes[pNode->index]->draw == true) {
				this->retrieveAll(nodes[pNode->firstChild + i], entRect);
			}
		}
	}
 
	for (int i = 0; i < pNode->count; i++) {
		returnObjects[returnObjectsCount + i] = elements[pNode->eleIndex + i];
	}

	returnObjectsCount += pNode->count;
}

void Quadtree::split(int pIndex, SDL_Rect pRect, int pDepth) {
	const int pHalfWidth = pRect.w >> 1;
	const int pHalfHeight = pRect.h >> 1;
	const int pMidX = pRect.x + pHalfWidth;
	const int pMidY = pRect.y + pHalfHeight;

	const int left = pRect.x;
	const int top = pRect.y;
	const int right = pMidX + pHalfWidth;
	const int bottom = pMidY + pHalfHeight;

	// top right
	SDL_Rect rect = SDL_Rect{ pMidX, top, pHalfWidth, pHalfHeight };
	createNewNode(nodes[nodeCount], pIndex + 0, pDepth + 1, rect);
	nodeCount++;

	// top left
	rect = SDL_Rect{ left, top, pHalfWidth, pHalfHeight };
	createNewNode(nodes[nodeCount], pIndex + 1, pDepth + 1, rect);
	nodeCount++;

	// bottom left
	rect = SDL_Rect{ left, pMidY, pHalfWidth, pHalfHeight };
	createNewNode(nodes[nodeCount], pIndex + 2, pDepth + 1, rect);
	nodeCount++;

	// bottom right
	rect = SDL_Rect{ pMidX, pMidY, pHalfWidth, pHalfHeight };
	createNewNode(nodes[nodeCount], pIndex + 3, pDepth + 1, rect);
	nodeCount++;
}

int Quadtree::getQuadrantIndex(SDL_Rect pRect, SDL_Rect entRect) {
	int index = -1;

	const int pHalfWidth = pRect.w >> 1;
	const int pHalfHeight = pRect.h >> 1;
	const int pMidX = pRect.x + pHalfWidth;
	const int pMidY = pRect.y + pHalfHeight;

	const int entBottom = entRect.y + entRect.h;
	const int entRight = entRect.x + entRect.w;

	// Object can completely fit within the top quadrants
	bool topQuadrant = (entRect.y < pMidY && entBottom <= pMidY);

	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (entRect.y >= pMidY);

	// Object can completely fit within the left quadrants
	if (entRect.x < pMidX && entRight <= pMidX) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (entRect.x >= pMidX) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}

IndexBitset Quadtree::getAllQuadrantIndices(SDL_Rect pRect, SDL_Rect entRect) {
	IndexBitset indices;

	const int pHalfWidth = pRect.w >> 1;
	const int pHalfHeight = pRect.h >> 1;
	const int pMidX = pRect.x + pHalfWidth;
	const int pMidY = pRect.y + pHalfHeight;

	// top right
	if (Physics::AABB(entRect, SDL_Rect{ pMidX, pRect.y, pHalfWidth, pHalfHeight })) {
		indices.set(0);
	}

	// top left
	if (Physics::AABB(entRect, SDL_Rect{ pRect.x, pRect.y, pHalfWidth, pHalfHeight })) {
		indices.set(1);
	}

	// bottom left
	if (Physics::AABB(entRect, SDL_Rect{ pRect.x, pMidY, pHalfWidth, pHalfHeight })) {
		indices.set(2);
	}

	// bottom right
	if (Physics::AABB(entRect, SDL_Rect{ pMidX, pMidY, pHalfWidth, pHalfHeight })) {
		indices.set(3);
	}

	return indices;
}

void Quadtree::checkCollision() {
	for (int i = 0; i < entities.size(); ++i) {
		auto& entityA = entities[i];

		if (entityA->hasComponent<ColliderComponent>()) {
			ColliderComponent& colA = entityA->getComponent<ColliderComponent>();

			if (colA.tag.compare("Movement") == 0 || colA.tag.compare("Sword") == 0 || colA.tag.compare("FireBall") == 0) {
				returnObjectsCount = 0;

				this->retrieveAll(nodes[0], colA.collider);

				for (int j = 0; j < returnObjectsCount; j++) {
					int entIndex = returnObjects[j];

					if (entIndex != i) {
						auto& entityB = entities[entIndex];

						ColliderComponent& colB = entityB->getComponent<ColliderComponent>();

						if (Physics::AABB(colA.collider, colB.collider)) {
							CollisionManager::handleCollision(entityA, entityB);
						}
					}
				}
			}
		}
	}
}

void Quadtree::cullEntities() {
	for (int i = 0; i < entities.size(); ++i) {
		if (entities[i]->hasComponent<SpriteComponent>()) {
			entities[i]->getComponent<SpriteComponent>().setCulled(true);
		}
	}

	returnObjectsCount = 0;

	this->retrieveAll(nodes[0], cullingBoundingBox);

	for (int j = 0; j < returnObjectsCount; j++) {
		int entIndex = returnObjects[j];
		entities[entIndex]->getComponent<SpriteComponent>().setCulled(false);
	}
}

void Quadtree::createNewNode(QuadtreeNode*& node, int index, int depth, SDL_Rect rect) {
	node->index = index;
	node->depth = depth;
	node->firstChild = -1;
	node->rect = rect;
	node->type = leafType;
	node->count = 0;
	node->eleIndex = -1; 
	node->dNodeIndex = -1;
	node->dNodeCount = 0;
	node->draw = true;
}

void Quadtree::CheckForNewEntities() {
	for (int i = static_cast<int>(entities.size() - 1); i >= 0 ; --i) {
		if (type == collisionType) {
			if (entities[i]->hasComponent<ColliderComponent>()) {
				if (!entityHeadCount.test(i)) {
					this->insert(nodes[0], entities[i]->getComponent<ColliderComponent>().collider, i);
					entityHeadCount.set(i);
				} else {
					return;
				}
			}
		} else if (type == cullingType) {
			if (entities[i]->hasComponent<SpriteComponent>()) {
				if (!entityHeadCount.test(i)) {
					this->insert(nodes[0], entities[i]->getComponent<SpriteComponent>().getDest(), i);
					entityHeadCount.set(i);
				} else {
					return;
				}
			}
		}
	}
}
