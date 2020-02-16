
#include "QuadtreeManager.h"
#include "../Game.h"
#include "../Texture/TextureManager.h"
#include "../ECS/Component.h"
#include "../Physics/Physics.h"
#include "Quadtree.h"

QuadtreeManager::QuadtreeManager(int width, int height, int tile) :
	collisionTree(width, height, tile, collisionType),// {
	cullingTree(width, height, tile, cullingType) {
}

QuadtreeManager::~QuadtreeManager() {
}

void QuadtreeManager::update() {

	auto start = std::chrono::steady_clock::now();

	collisionTree.update();
	cullingTree.update();

	auto end = std::chrono::steady_clock::now();

	auto diff = end - start;

	auto time = std::chrono::duration<double, std::milli>(diff).count();

	//std::cout << "quadtree update: " << time << std::endl;
}

void QuadtreeManager::draw() {
	collisionTree.draw();
	cullingTree.draw();
}
