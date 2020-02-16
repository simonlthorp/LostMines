#include "Scene.h"
#include <iostream>

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init() {
	std::cout << "Intializing Scene" << std::endl;
}

void Scene::handleEvents() {

}

void Scene::update() {

}

void Scene::lateUpdate() {

}

void Scene::render() {

}

void Scene::loadScene() {
	std::cout << "Loading Scene" << std::endl;
}

void Scene::loadData(std::vector<std::string> data) {
	//Do nothing with it
}


//
////Mouse
//void Scene::updateMouse() {
//	//Shoot at mouse cursor
//	if (SDL_GetMouseState(&mouse_x, &mouse_y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
//		//left click
//		std::cout << getMouseX() << " " << getMouseY() << std::endl;
//		for (int i = 0; i < uiComponents.size(); i++) {
//			if (uiComponents.at(i).withinUI(getMouseX(), getMouseY())) {
//				//if (uiComponents.at(i).getID() == "button") {
//					//Calls the Scene Manager to switch to next Scene
//					//SceneManager::incrementLoadGame();
//					//SceneManager::loadGame = 1;
//				//}
//				std::cout << uiComponents.at(i).getID() << " Started Loading" << std::endl;
//			}
//		}
//	}
//	else {
//		//nothing??
//	}
//}
//
//int Scene::getMouseX() {
//	return mouse_x;
//}
//
//int Scene::getMouseY() {
//	return mouse_y;
//}