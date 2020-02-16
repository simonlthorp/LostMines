#pragma once
#include "../UI/UI.h"
#include <vector>
#include <stdio.h>
#include <iostream>

class Scene {
public:
	Scene();
	~Scene();

	//default
	virtual void init();
	virtual void handleEvents();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();
	virtual void loadScene();
	//void updateMouse();
	//int getMouseX();
	//int getMouseY();
	virtual void loadData(std::vector<std::string> data);
protected:
	//std::vector<UI> uiComponents;
	//int mouse_x;
	//int mouse_y;
};