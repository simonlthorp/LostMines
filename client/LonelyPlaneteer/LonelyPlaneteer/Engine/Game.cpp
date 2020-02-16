#include "Game.h"
//SDL Includes
#include "SDL_ttf.h"
//C++ Includes
#include <iostream>
//Engine Includes
#include "Camera.h"
#include "Texture/TextureManager.h"
#include "ECS/ECS.h"
#include "ECS/Vector2D.h"
#include "../Game/UI/TextUI.h"


SDL_Rect Game::camera;

SceneManager Game::sceneManager;
AssetManager Game::assetManager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Window* Game::window = nullptr;
std::mutex Game::rendering;

Game::Game() {};
Game::~Game() {};

//------ Label -------
TextUI* fpsText = nullptr;
TextUI* fpsMinText = nullptr;
TextUI* fpsMaxText = nullptr;
//------ Label -------

int Game::screen_height = 0;
int Game::screen_width = 0;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;
		
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		screen_height = height;
		screen_width = width;
		if (window) {
			std::cout << "Window Created" << std::endl;

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer Created" << std::endl;
				isRunning = true;
			} else {
				isRunning = false;
			}
		}
	}

	if (TTF_Init() == -1) {
		std::cout << "Failed to initalize TTF Library.";
	}

	camera = { 0, 0, width, height};

	//Init audio
	Game::mixer->init();

	//init static's here
	assetManager.init();
	sceneManager.init();

	SDL_Color labelColor = { 255, 255, 255, 255 };
	SDL_Rect labelPosition;
	labelPosition.x = 10;
	labelPosition.y = 10;
	fpsText = new TextUI("fpsText", UILabels::text, "Arial_12", labelPosition, labelColor, "00");
	labelPosition.y = 20;
	fpsMinText = new TextUI("fpsMinText", UILabels::text, "Arial_12", labelPosition, labelColor, "00");
	labelPosition.y = 30;
	fpsMaxText = new TextUI("fpsMaxText", UILabels::text, "Arial_12", labelPosition, labelColor, "00");

	ticks = SDL_GetTicks();
}

void Game::resetCamera() {
	camera = { 0, 0, screen_width, screen_height };
}

void Game::handleEvents() {
	//Scene HandeleEvents here
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event) != 0) {
		if (keys[SDL_SCANCODE_ESCAPE]) {
			isRunning = false;
		}

		Game::sceneManager.handleEvents();
	}
}

void Game::update() {
	//Scene update here
	Game::sceneManager.update();
}

void Game::lateUpdate() {
	//called after everything has finished updating
	Game::sceneManager.lateUpdate();
}

void Game::render() {
	rendering.lock();
	//beginning = std::chrono::duration_cast<std::chrono::milliseconds>(
	//	std::chrono::system_clock::now().time_since_epoch()
	//);


	//std::cout << "Clearing Renderer" << std::endl;
	SDL_RenderClear(renderer);
	//std::cout << "Rendering New Images" << std::endl;
	//Scene render here
	Game::sceneManager.render();
	//std::cout << "Presenting Images" << std::endl;

	//------ Label -------
	frame++;
	if (SDL_GetTicks() - ticks > 1000) {
		fpsText->changeText("Current: " + std::to_string(frame));

		if (minimumTime > frame) {
			minimumTime = frame;
			fpsMinText->changeText("Minimum: " + std::to_string(minimumTime));
		}
		if (maximumTime < frame) {
			maximumTime = frame;
			fpsMaxText->changeText("Maximum: " + std::to_string(maximumTime));
		}

		ticks = SDL_GetTicks();
		frame = 0;
	}
	fpsText->render();
	fpsMinText->render();
	fpsMaxText->render();
	//------ Label -------

	SDL_RenderPresent(renderer);
	//std::cout << "Finished Rendering" << std::endl;
	rendering.unlock();
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Mix_FreeMusic(Game::mixer->menu_music);
	Mix_FreeMusic(Game::mixer->game_music);
	/*
	Mix_FreeChunk(GameScene::mixer->laserShot->sfx);
	Mix_FreeChunk(GameScene::mixer->ricochet->sfx);
	Mix_FreeChunk(GameScene::mixer->ricochet_metal->sfx);
	*/
	Mix_Quit();
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

SDL_Window* Game::getWindow() {
	return window;
}
