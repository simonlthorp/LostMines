#pragma once
//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
//Engine Includes
#include "MapData.h"
//C++ Includes
#include <mutex>
#include <thread>

class MapManager {
public:
	MapManager();
	~MapManager();

	int getMapWidth();
	int getMapHeight();
	MapData* getMap();
	int** getMapInfo();

	void loadMap();
	bool withinMapAndNotPath(int** tmpMap, int height, int width);
	SDL_Rect getCenterPoint();
	void drawAllColiders();
	void drawCollisions();
	void drawOuterCollider();
	void drawMap();
private:
	SDL_Rect src, dest;
	SDL_Texture *dirt;
	SDL_Texture *water;
	SDL_Texture *grass;
	MapData* map;

	//Threading
	std::mutex entity_mtx;
	int threadCounter = 0;

	void threadInnerCollider(int id, int starti, int endi, int startj, int endj);
	void threadWallCollider(int id, bool horizontal, int straitValue);
};