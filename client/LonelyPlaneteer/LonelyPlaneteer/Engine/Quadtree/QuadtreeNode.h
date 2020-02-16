#pragma once

#include "SDL.h"
#include <vector>

#define MAX_OBJECTS 16
#define MAX_DEPTH 6

#define ELEMENT_NODE_BUFFER_SIZE 256
#define ELEMENT_BUFFER_SIZE 1024000
#define COLLISION_RETRIEVAL_BUFFER_SIZE 500
#define CULLING_RETRIEVAL_BUFFER_SIZE 5000

#define NODES_BUFFER_SIZE 10000

#define ENTITIES_BITSET_BUFFER_SIZE 50000

enum QuadtreeNodeType : std::size_t {
	nodeType,
	leafType
};

struct QuadtreeNode {
	int index;
	int depth;
	int firstChild;
	SDL_Rect rect;
	QuadtreeNodeType type;
	//int* elements;
	int count;
	int eleIndex;
	int dNodeIndex;
	int dNodeCount;
	bool draw;
};

struct DynamicQuadtreeNode {
	int index;
	int eleIndex;
	int localIndex;
	int entIndex;
	QuadtreeNode& pNode;
};
