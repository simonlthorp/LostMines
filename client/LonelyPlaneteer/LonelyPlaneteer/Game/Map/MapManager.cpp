#include "MapManager.h"
//Engine Includes
#include "../../Engine/Game.h"
#include "../Objects/Wall.h"
#include "../Objects/FireballWall.h"
#include "../Objects/Tile.h"
//C++ Includes
#include <chrono>
#include <iostream>
#include <fstream>
#include <Windows.h>

MapManager::MapManager() {
	dirt = Game::assetManager.getTexture("dirt");
	grass = Game::assetManager.getTexture("grass");
	water = Game::assetManager.getTexture("water");

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dest.w = 32;
	dest.h = 32;
	dest.x = 0;
	dest.y = 0;

	map = new MapData();

	loadMap();
}

MapManager::~MapManager() {
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
}

int MapManager::getMapWidth() { return map->width; }
int MapManager::getMapHeight() { return map->height; }
MapData* MapManager::getMap() { return map; }
int** MapManager::getMapInfo() { return map->map; }

void MapManager::loadMap() {
	//Prints out current directory location
	//char buf[256];
	//GetCurrentDirectoryA(256, buf);
	//std::cout << buf << std::endl;

	//Uses Windows.h to get file names in directory
	std::string path = "Assets/Maps/Local/";
	std::vector<std::string> v; //Files in directory;

	std::string pattern(path);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}

	//Prints out files inside folder location
	//Starts at i = 2 to skip hidden pathings
	std::vector<MapData> maps;
	for (int i = 2; i < v.size(); i++) {
		//Prints out name of the file
		std::cout << v.at(i) << std::endl;

		//Creates stream for file
		std::ifstream file(path + v.at(i));
		//std::ifstream file("Assets/Maps/LostMinesTestMap_GroundLayer.csv");
		if (!file.is_open()) {
			std::cout << "Failed to load" << std::endl;
		}

		MapData tmpMap;
		int** tmp = nullptr;
		std::string value;
		std::vector<std::string> lines;
		int counter = 1;
		while (file.good()) {
			switch (counter) {
			case 1:
				std::getline(file, value);
				//std::cout << "Name: " << value << std::endl;
				tmpMap.name = value;
				counter++;
				break;
			case 2:
				std::getline(file, value);
				//std::cout << "Height: " << value << std::endl;
				tmpMap.height = std::stoi(value);
				std::cout << "File Size: " << tmpMap.height << std::endl;
				tmp = new int*[tmpMap.height];
				counter++;
				break;
			case 3:
				std::getline(file, value);
				//std::cout << "Width: " << value << std::endl;
				tmpMap.width = std::stoi(value);
				for (int i = 0; i < tmpMap.height; i++) {
					tmp[i] = new int[tmpMap.width]{ 1 };
				}
				counter++;
				break;
			case 4:
				for (int i = 0; i < tmpMap.height; i++) {
					for (int j = 0; j < tmpMap.width; j++) {
						std::getline(file, value, ',');
						//if (j == tmpMap.width - 1) {
						//	std::getline(file, value, ',');
						//}
						//std::cout << value;
						//if (std::stoi(value)) {
						tmp[i][j] = std::stoi(value);
						//}
						//std::cout << value;
					}
				}
				break;
			}
			//Prints out file insides
			//std::getline(file, value);
			//std::cout << value.length() << " Length" << std::endl;
			//lines.push_back(value);
			//std::cout << value << std::endl;
		}
		//std::cout << std::endl << "Map:" << tmpMap.name << std::endl;
		for (int i = 0; i < tmpMap.height; i++) {
			for (int j = 0; j < tmpMap.width; j++) {
				//std::cout << tmp[i][j];
			}
			//std::cout << std::endl;
		}
		tmpMap.map = tmp;
		//if (tmpMap.name != "TestMap") {
			maps.push_back(tmpMap);
		//}

	}

	/*
	map->height = maps.at(0).height;
	map->width = maps.at(0).width;
	map->map = maps.at(0).map;
	int **mapInfo = map->map;
	int type = 0;
	for (int row = 0; row < map->height; row++) {
		for (int col = 0; col < map->width; col++) {
			type = mapInfo[row][col];
			//std::cout << "Type: " << type << std::endl;
			if (type != -1) {
				GameScene::manager.addNewEntity(new Tile(static_cast<float>(col * 32), static_cast<float>(row * 32), type, layerLabels::layer0));
			}
		}
	}
	*/

	for (MapData m : maps) {
		map->height = m.height;
		map->width = m.width;
		map->map = m.map;
		layerLabels layer;
		if (m.name == "CollisionFireball") {
			layer = layerLabels::bottomLayer;
		}
		else if (m.name == "CollisionLayer") {
			layer = layerLabels::bottomLayer;
		}
		else if (m.name == "GroundDecoration") {
			layer = layerLabels::layer1;
		}
		else if (m.name == "GroundLayer") {
			layer = layerLabels::layer0;
		}
		else if (m.name == "RoofDecoration") {
			layer = layerLabels::layer5;
		}
		else if (m.name == "RoofLayer") {
			layer = layerLabels::layer4;
		}
		else if (m.name == "WallDecoration") {
			layer = layerLabels::layer3;
		}
		else if (m.name == "WallLayer") {
			layer = layerLabels::layer2;
		}

		if (m.name == "CollisionFireball") {
			int **mapInfo = m.map;
			int type = 0;
			for (int row = 0; row < map->height; row++) {
				for (int col = 0; col < map->width; col++) {
					type = mapInfo[row][col];
					if (type != -1) {
						GameScene::manager.addNewEntity(new FireballWall(nullptr, static_cast<float> (col * 32), static_cast<float> (row * 32)));
					}
				}
			}
		}

		// create tile entities and add to manager
		int **mapInfo = m.map;
		int type = 0;
		for (int row = 0; row < map->height; row++) {
			for (int col = 0; col < map->width; col++) {
				type = mapInfo[row][col];
				if (type != -1) {
					GameScene::manager.addNewEntity(new Tile(static_cast<float>(col * 32), static_cast<float>(row * 32), type, layer));
				}
			}
		}
	}
	
	//Pulls last for collision
	map->height = maps.at(1).height;
	map->width = maps.at(1).width;
	map->map = maps.at(1).map;


	/**
	for (MapData m : maps) {
		//map->height = maps.at(3).height;
		//map->width = maps.at(3).width;
		//map->map = maps.at(3).map;

		map->height = m.height;
		map->width = m.width;
		map->map = m.map;
		layerLabels layer;
		if (m.name == "Decoration1") {
			layer = layerLabels::layer2;
		}
		else if (m.name == "Decoration2") {
			layer = layerLabels::layer3;
		}
		else if (m.name == "Decoration3") {
			layer = layerLabels::layer4;
		}
		else if (m.name == "Decoration4") {
			layer = layerLabels::layer2;
		}
		else if (m.name == "GroundLayer") {
			layer = layerLabels::layer0;
		}
		else if (m.name == "RoofDecoration") {
			layer = layerLabels::layer5;
		}
		else if (m.name == "Roofs") {
			layer = layerLabels::layer6;
		}
		else if (m.name == "WallDecoration") {
			layer = layerLabels::layer2; // after this one is player!
		}
		else if (m.name == "Walls") {
			layer = layerLabels::layer1;
		}

		// create tile entities and add to manager
		int **mapInfo = m.map;
		int type = 0;
		for (int row = 0; row < map->height; row++) {
			for (int col = 0; col < map->width; col++) {
				type = mapInfo[row][col];
				if (type != -1) {
					GameScene::manager.addNewEntity(new Tile(static_cast<float>(col * 32), static_cast<float>(row * 32), type, layer));
					if (m.name == "Decoration2") {
						GameScene::manager.addNewEntity(new Wall(nullptr, static_cast<float> (col * 32), static_cast<float> (row * 32)));
					}
				}
			}
		}
	}
	**/
}

bool MapManager::withinMapAndNotPath(int** tmpMap, int height, int width) {
	if (height >= 0 && height < map->height && width >= 0 && width < map->width) {
		if (tmpMap[height][width] != 0 && tmpMap[height][width] != 2) {
			return true;
		}
	}
	return false;
}


SDL_Rect MapManager::getCenterPoint() {
	SDL_Rect center;
	int centerHeight = map->height / 2;
	int centerWidth = map->width / 2;
	center.x = centerWidth * 32;
	center.y = centerHeight * 32;
	return center;
}

void MapManager::drawAllColiders() {
	drawCollisions();
	drawOuterCollider();
	//SceneManager::threadCount = SceneManager::threadList.size();
	for (int i = 0; i < SceneManager::threadList.size(); i++) {
		SceneManager::threadList.at(i).detach();
	}
	//std::this_thread::sleep_for(std::chrono::seconds(30));
	std::cout << "Total number of threads: " << SceneManager::threadList.size() << std::endl;
}

void MapManager::drawCollisions() {
	int numberOfSection = 2; // 2 sections = 4 divisions.. 4 sections = 16 divisions.. aka. numberOfSection^2
	int heightSection = map->height / numberOfSection;
	int widthSection = map->width / numberOfSection;
	for (int i = 0; i < numberOfSection; i++) {
		for (int j = 0; j < numberOfSection; j++) {
			SceneManager::threadList.push_back(std::thread(&MapManager::threadInnerCollider, this, static_cast<int> (SceneManager::threadList.size() + 1), (heightSection * i), (heightSection * (i + 1)), (widthSection * j), (widthSection * (j + 1))));
		}
	}
}

void MapManager::drawOuterCollider() {
	Wall* tmpWall = nullptr;
	int topRow = -1; //starts at top row
	int bottomRow = map->height; //starts at bottom row
	int leftColumn = -1; //starts at left column
	int rightColumn = map->width; //starts at right column
	//Top Wall
	SceneManager::threadList.push_back(std::thread(&MapManager::threadWallCollider, this, static_cast<int> (SceneManager::threadList.size() + 1), true, topRow));
	//Bottom Wall
	SceneManager::threadList.push_back(std::thread(&MapManager::threadWallCollider, this, static_cast<int> (SceneManager::threadList.size() + 1), true, bottomRow));
	//Left Wall
	SceneManager::threadList.push_back(std::thread(&MapManager::threadWallCollider, this, static_cast<int> (SceneManager::threadList.size() + 1), false, leftColumn));
	//Right Wall
	SceneManager::threadList.push_back(std::thread(&MapManager::threadWallCollider, this, static_cast<int> (SceneManager::threadList.size() + 1), false, rightColumn));
}

void MapManager::threadInnerCollider(int id, int starti, int endi, int startj, int endj) {
	SceneManager::incrementThreadCount();
	std::chrono::milliseconds begining = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch() );
	int** mapInfo = map->map;
	//SDL_Texture* texture = Game::assetManager.getTexture("desert");
	for (int row = starti; row < endi; row++) {
		for (int col = startj; col < endj; col++) {
			//std::cout << "thread: " << row << ":" << col << std::endl;
			entity_mtx.lock();
			if (mapInfo[row][col] == 199 || mapInfo[row][col] == 198 || mapInfo[row][col] == 197 || mapInfo[row][col] == 190 || mapInfo[row][col] == 195 || mapInfo[row][col] == 193 || mapInfo[row][col] == 194 || mapInfo[row][col] == 192 || mapInfo[row][col] == 200 || mapInfo[row][col] == 201 || mapInfo[row][col] == 202 || mapInfo[row][col] == 203 || mapInfo[row][col] == 204 || mapInfo[row][col] == 205 || mapInfo[row][col] == 206 || mapInfo[row][col] == 207 || mapInfo[row][col] == 212 || mapInfo[row][col] == 213 || mapInfo[row][col] == 214 || mapInfo[row][col] == 220 || mapInfo[row][col] == 221 || mapInfo[row][col] == 222 || mapInfo[row][col] == 228 || mapInfo[row][col] == 229 || mapInfo[row][col] == 230) {
				GameScene::manager.addNewEntity(new Wall(nullptr, static_cast<float> (col * 32), static_cast<float> (row * 32)));
			}
			entity_mtx.unlock();
		}
	}

	std::chrono::milliseconds ending = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds total = ending - begining;
	std::cout << "Thread Finished " << id << " sections: " << starti << "," << endi << " : " << startj << "," << endi << " in: " << (total.count()) << " (milliseconds)" << std::endl;
	SceneManager::decrementThreadCount();
	SceneManager::checkThreadCount();
}

void MapManager::threadWallCollider(int id, bool horizontal, int straitValue) {
	SceneManager::incrementThreadCount();
	SDL_Texture* texture = Game::assetManager.getTexture("tileset");
	if (horizontal) {
		for (int i = -1; i < map->width + 1; i++) {
			entity_mtx.lock();
			GameScene::manager.addNewEntity(new Wall(texture, static_cast<float> (i * 32), static_cast<float> (straitValue * 32)));
			entity_mtx.unlock();
			//std::cout << topRow << " " << i << " : ";
		}
	}
	else if (!horizontal) {
		for (int i = -1; i < map->height + 1; i++) {
			entity_mtx.lock();
			GameScene::manager.addNewEntity(new Wall(texture, static_cast<float> (straitValue * 32), static_cast<float> (i * 32)));
			entity_mtx.unlock();
			//std::cout << i << " " << leftColumn << " : ";
		}
	}

	std::cout << "Wall Thread " << id << " Finished: " << horizontal << ": " << straitValue << std::endl;
	SceneManager::decrementThreadCount();
	SceneManager::checkThreadCount();
}

void MapManager::drawMap() {
	int **mapInfo = map->map;
	int type = 0;
	for (int row = 0; row < map->height; row++) {
		for (int col = 0; col < map->width; col++) {
			type = mapInfo[row][col];
			dest.x = col * 32;
			dest.y = row * 32;
			src.x = (type % 8) * 32;
			src.y = (type / 8) * 32;
			//std::cout << src.x << ":" << src.y << std::endl;
			TextureManager::Draw(Game::assetManager.getTexture("tileset"), src, dest, 0);
		}
	}
}