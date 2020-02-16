#pragma once
//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
//Game Includes
#include "SceneManager/SceneManager.h"
#include "AssetManager/AssetManager.h"
//C++ Includes
#include <mutex>
#include <chrono>


class Game {
public:

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void lateUpdate();
	void render();
	void clean();

	bool running() {return isRunning;}

	static void resetCamera();
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Window* window;
	static SDL_Rect camera;
	static SDL_Window* getWindow();
	static SceneManager sceneManager;
	static AssetManager assetManager;
	static std::mutex rendering;

	static AudioMixer* mixer;
	//static Mix_Music* menu_music;

private:
	static int screen_height;
	static int screen_width;

	bool isRunning;
	//int beginning;
	//int ending;
	int ticks;
	int frame = 0;

	long minimumTime = 1000000000;
	long maximumTime = 0;
};