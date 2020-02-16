#pragma once

#include "../ECS/ECS.h"
#include "../Game.h"
#include "QuadtreeNode.h"
#include "../ECS/Component.h"

#include "../Physics/CollisionManager.h"

#include <vector>
#include <list>

enum QuadtreeType : std::size_t {
	collisionType,
	cullingType
};

using IndexBitset = std::bitset<std::size_t(4)>;
using HeadCount = std::bitset<std::size_t(ENTITIES_BITSET_BUFFER_SIZE)>;

class Quadtree {
public:
	Quadtree(int width, int height, int tile, QuadtreeType t, bool isStatic = false, bool drawing = false);
	~Quadtree();

	void update();
	void draw();	

private:
	int mapWidth;
	int mapHeight;
	int tileSize;

	QuadtreeType type;

	SDL_Rect boundingBox;
	SDL_Rect cullingBoundingBox;

	int cullingScaleOffset;

	std::vector<std::unique_ptr<Entity>>& entities;

	QuadtreeNode** nodes;
	int nodeCount;

	DynamicQuadtreeNode** dynamicNodes;
	int dynamicNodeCount;

	int* elements;
	int eleNodeCount;

	int* returnObjects;
	int returnObjectsCount;

	bool drawingEnabled;

	HeadCount entityHeadCount;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	void buildTree();

	void updateTree();

	void insert(QuadtreeNode* pnode, SDL_Rect entRect, int entIndex);

	void cleanup();

	void retrieveAll(QuadtreeNode* pNode, SDL_Rect entRect);

	void split(int pIndex, SDL_Rect pRect, int pDepth);

	int getQuadrantIndex(SDL_Rect pRect, SDL_Rect entRect);

	IndexBitset getAllQuadrantIndices(SDL_Rect pRect, SDL_Rect entRect);

	void checkCollision();

	void cullEntities();

	void createNewNode(QuadtreeNode*& node, int index, int depth, SDL_Rect rect);

	void CheckForNewEntities();
};
