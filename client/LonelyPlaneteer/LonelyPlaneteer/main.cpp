#include "Engine/Game.h"
#include <time.h>

#include "Game/Components/GamepadInputComponent.h"

Game *game = nullptr;

int GamepadInput::CurrentGamepadsOpen = 0;

int main(int argc, char *argv[]) {

	const int FPS = 60;

	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	srand(static_cast<unsigned>(time(NULL)));

	game = new Game();
	game->init("Lonely Planeteer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
	while (game->running()) {
		
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->lateUpdate();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}