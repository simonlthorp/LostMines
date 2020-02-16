#pragma once
#ifndef MenuScene_h
#define MenuScene_h

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
#include "../../Engine/Audio/AudioMixer.h"

class AudioMixer;

class MenuScene : public Scene {
public:
	MenuScene();
	~MenuScene();

	void init() override;
	void handleEvents() override;
	void update() override;
	void render() override;
	void loadScene() override;
	AudioMixer* mixer;

	//Mouse
	void updateMouse();
	int getMouseX();
	int getMouseY();
private:

	//Label ------------
	TextUI* titleText = nullptr;
	//------------------

	std::vector<UI*> uiComponents;

	//Mouse
	bool mouseDown = false;
	int mouse_x;
	int mouse_y;
};
#endif