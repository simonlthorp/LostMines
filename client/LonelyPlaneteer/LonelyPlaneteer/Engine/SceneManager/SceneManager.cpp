#include "SceneManager.h"
//C++ Includes
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <Windows.h>

std::atomic<int> SceneManager::loadGame;
std::atomic<int> SceneManager::threadCount;
std::vector<std::thread> SceneManager::threadList;
std::mutex SceneManager::variable_mutex;
std::map<std::string, Scene*> SceneManager::scenes;
Scene* SceneManager::currentScene;

SceneManager::SceneManager() {
	loadGame = 0;
	threadCount = 0;
}
SceneManager::~SceneManager() {}

void SceneManager::init() {
	//CHANGE THIS HERE TO 2 for GameScene
	loadGame = 0;
	threadCount = 0;
	GameScene* gameScene = new GameScene();
	MenuScene* menuScene = new MenuScene();
	LoadingScene* loadScene = new LoadingScene();
	SettingsScene* settingsScene = new SettingsScene();
	JoinScene* joinScene = new JoinScene();
	LobbyScene* lobbyScene = new LobbyScene();
	menuScene->init();
	gameScene->init();
	loadScene->init();
	settingsScene->init();
	joinScene->init();
	lobbyScene->init();
	scenes.emplace("menuScene", menuScene);
	scenes.emplace("gameScene", gameScene);
	scenes.emplace("loadScene", loadScene);
	scenes.emplace("settingsScene", settingsScene);
	scenes.emplace("joinScene", joinScene);
	scenes.emplace("lobbyScene", lobbyScene);
	currentScene = scenes["menuScene"];
}

void SceneManager::handleEvents() {
	currentScene->handleEvents();
}

void SceneManager::update() {
	currentScene->update();
}

void SceneManager::lateUpdate() {
	currentScene->lateUpdate();
}

void SceneManager::render() {
	currentScene->render();
}

void SceneManager::changeScenes(std::string name, bool withLoad) {
	if (name == "gameScene" && withLoad) {
		SceneManager::changeScenes("loadScene");
		std::thread somethread = std::thread(&SceneManager::trackNumberOfThreads, name);
		somethread.detach();
	} else {
		//std::cout << "Changing Scene: " << name << std::endl;
		currentScene = scenes[name];
	}
}

void SceneManager::changeScenes(std::string name, std::vector<std::string> data, bool withLoad) {
	if (name == "gameScene" && withLoad) {
		SceneManager::changeScenes("loadScene");
		std::thread somethread = std::thread(&SceneManager::trackNumberOfThreads, name);
		somethread.detach();
	}
	else {
		//std::cout << "Changing Scene: " << name << std::endl;
		currentScene = scenes[name];
		currentScene->loadData(data);
	}
}

void SceneManager::trackNumberOfThreads(std::string name) {
	while (true) {
		////If threadCount is not atomic, it needs mutex lock for read and write conflict.
		//SceneManager::variable_mutex.lock(); //
		if (SceneManager::threadCount <= 0) {
			//std::cout << "Breaking?" << std::endl;
			break;
		}
		//SceneManager::variable_mutex.unlock();
	}
	//std::cout << "Finished Loading" << std::endl;
	SceneManager::changeScenes(name);
}


//----------------------------------
// Used by parallel threads when running.
// See MapManager for examples

void SceneManager::incrementLoadGame() {
	variable_mutex.lock();
	loadGame++;
	variable_mutex.unlock();
}

void SceneManager::decrementLoadGame() {
	variable_mutex.lock();
	loadGame--;
	variable_mutex.unlock();
}

//DANGER WHEN SETTING THIS!
void SceneManager::setLoadGame(int value) {
	variable_mutex.lock();
	loadGame = value;
	variable_mutex.unlock();
}

void SceneManager::incrementThreadCount() {
	variable_mutex.lock();
	threadCount++;
	variable_mutex.unlock();
}

void SceneManager::decrementThreadCount() {
	variable_mutex.lock();
	threadCount--;
	variable_mutex.unlock();
}

//DANGER WHEN SETTING THIS!
void SceneManager::setThreadCount(int value) {
	variable_mutex.lock();
	threadCount = value;
	variable_mutex.unlock();
}

void SceneManager::checkThreadCount() {
	variable_mutex.lock();
	//std::cout << "Thread Count: (" << threadList.size() << "/" << (threadList.size() - threadCount) << ")" << std::endl;
	variable_mutex.unlock();
}

Scene* SceneManager::getScene(std::string name) {
	if (scenes[name] != nullptr) {
		return scenes[name];
	}
	return nullptr;
}