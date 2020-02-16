#pragma once
#ifndef LobbyScene_h
#define LobbyScene_h

//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//Engine Includes
#include "../UI/UI.h"
#include "../UI/TextUI.h"
#include "../UI/TextInputUI.h"
#include "Scene.h"
//#include "MenuSceneUI.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class LobbyScene : public Scene {
public:
	LobbyScene();
	~LobbyScene();

	void init() override;
	void handleEvents() override;
	void update() override;
	void render() override;
	void loadScene() override;
	void loadData(std::vector<std::string> data) override;

	void addPlayer(int value, std::string name, int class_type);

	//Mouse
	void updateMouse();
	void updateKeyboardInput();
	int getMouseX();
	int getMouseY();
private:
	static bool ready[4];
	//SDL_Rect src, dest, srcTitle, destTitle, srcBackground, destBackground;

	//Label ------------

	//------------------

	std::vector<UI*> uiComponents;
	TextInputUI* currentInputEnabled = nullptr;

	//Mouse
	bool mouseDown = false;
	int mouse_x;
	int mouse_y;
};

#endif
