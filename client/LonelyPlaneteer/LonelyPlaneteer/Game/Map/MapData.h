#pragma once
#include <string>

struct MapData {
	MapData() { /* Warning this will cause errors if data members are not set after */ }
	MapData(std::string name, int** map, int width, int height) : name(name), map(map), width(width), height(height) {}
	std::string name;
	int **map;
	int width;
	int height;
};
