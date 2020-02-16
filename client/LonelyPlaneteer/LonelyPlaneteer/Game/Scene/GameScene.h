#pragma once
//CPP includes
#include <stdio.h>
#include <iostream>
#include <thread>
//SDL includes
#include "SDL.h"
#include "SDL_image.h"
//ENGINE includes
#include "../../Engine/ECS/ECS.h"
#include "Scene.h"
//Game Includes
#include "../UI/TextUI.h"
//#include "AudioMixer.h"

enum GroupLabels : std::size_t {
	wallGroup,
	playersGroup,
	enemiesGroup,
	mineGroup, 
	projectileGroup,
	mobArea
};

enum layerLabels : std::size_t {
	bottomLayer,
	layer0, //Ground Layer
	layer1, //Walls
	layer2, //Decoration
	layer3, //Decoration2
	
	topLayer, //NOT USED AT ALL??? ALL ENTITIES
	
	layer4, //Decoration3
	layer5, //Roofs

	layer6, //Roof Decorations
	layer7, // NOT USED
	layer8, // NOT USED

	/*
	bottomLayer,
	layer0, //Ground Layer
	layer1, //Walls
	layer2, //Decoration
	layer3, //Decoration2
	layer4, //Decoration3
	topLayer, //NOT USED AT ALL??? ALL ENTITIES

	layer5, //Roofs
	layer6, //Roof Decorations

	layer7, // NOT USED
	layer8, // NOT USED
	*/
};

class GameScene : public Scene {
public:
	static Manager manager;
	//static AudioMixer* mixer;
	GameScene();
	~GameScene();

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	void init() override;
	void handleEvents() override;
	void update() override;
	void lateUpdate() override;
	void render() override;
	void loadScene() override;
	void spawnNewTestEntity();
	void createTeams();
	void createTeamsLocal();
	void setGameOverState(bool display);
	void updateScore();
	void resetScore();
	void setMaxPoints(int maxScore);
	bool checkForWinner();
	//Mouse
	void updateMouse();
	int getMouseX();
	int getMouseY();

	bool getGamepadAButton(int id);
	bool isLocal;
private:
	UI* background = nullptr;
	TextUI* gameOverText = nullptr;

	std::vector<UI*> uiComponents;
	//Mouse
	bool mouseDown = false;
	int mouse_x;
	int mouse_y;

	// Team Scores
	int redScore = 0;
	int blueScore = 0;

	int goal = 100000;

	int winningTeam = 0;


};