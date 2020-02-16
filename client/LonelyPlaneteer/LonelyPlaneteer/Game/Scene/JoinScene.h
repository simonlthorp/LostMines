#pragma once

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

class JoinScene : public Scene {
public:
	JoinScene();
	~JoinScene();

	void init() override;
	void handleEvents() override;
	void update() override;
	void render() override;
	void loadScene() override;

	//Mouse
	void updateMouse();
	void updateKeyboardInput();
	int getMouseX();
	int getMouseY();
private:
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
