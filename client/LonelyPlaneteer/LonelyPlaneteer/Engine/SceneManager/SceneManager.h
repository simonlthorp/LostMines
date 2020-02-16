#pragma once

//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
//Engine Includes
#include "../ECS/ECS.h"
#include "../../Game/Scene/Scene.h"
#include "../../Game/Scene/GameScene.h"
#include "../../Game/Scene/LoadingScene.h"
#include "../../Game/Scene/MenuScene.h"
#include "../../Game//Scene/SettingsScene.h"
#include "../../Game//Scene/JoinScene.h"
#include "../../Game//Scene/LobbyScene.h"
//C++ Includes
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <map>
#include <atomic>
#include <vector>

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	//static LoadingScene loadScene;
	void init();
	void handleEvents();
	void update();
	void lateUpdate();
	void render();
	static void changeScenes(std::string name, bool withLoad = false);
	static void changeScenes(std::string name, std::vector<std::string> data, bool withLoad = false);

	//----------------------------------------
	static void incrementLoadGame();
	static void decrementLoadGame();
	//DANGER WHEN SETTING THIS!
	static void setLoadGame(int value);
	static void incrementThreadCount();
	static void decrementThreadCount();
	//DANGER WHEN SETTING THIS!
	static void setThreadCount(int value);
	static void checkThreadCount();
	static void trackNumberOfThreads(std::string name);
	static std::atomic<int> loadGame;
	static std::atomic<int> threadCount;
	static std::vector<std::thread> threadList;
	static std::mutex variable_mutex;
	static Scene* getScene(std::string name);

	//----------------------------------------
private:
	static std::map<std::string, Scene*> scenes;
	static Scene* currentScene;
};