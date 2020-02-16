#pragma once

#include "SDL.h"
#include "../ECS/ECS.h"
#include "../../Game/Map/MapData.h"
#include "../../Game/Objects/Player.h"
#include "QuadtreeNode.h"
#include "Quadtree.h"

#include <vector>

class QuadtreeManager {
public:
	QuadtreeManager(int width, int height, int tile);
	~QuadtreeManager();

	void update();
	void draw();

private:
	Quadtree collisionTree;
	Quadtree cullingTree;
};
