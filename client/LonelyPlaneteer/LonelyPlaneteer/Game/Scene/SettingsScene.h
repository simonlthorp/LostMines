#pragma once
#ifndef SettingsScene_h
#define SettingsScene_h

//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//Engine Includes
#include "../UI/UI.h"
#include "../UI/TextUI.h"
#include "Scene.h"
//#include "MenuSceneUI.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class SettingsScene : public Scene {
public:
	SettingsScene();
	~SettingsScene();

	void init() override;
	void handleEvents() override;
	void update() override;
	void render() override;
	void loadScene() override;

	//Mouse
	void updateMouse();
	int getMouseX();
	int getMouseY();
private:
	//SDL_Rect src, dest, srcTitle, destTitle, srcBackground, destBackground;

	//Label ------------

	//------------------

	std::vector<UI*> uiComponents;
	//Mouse
	bool mouseDown = false;
	int mouse_x;
	int mouse_y;
};

#endif
