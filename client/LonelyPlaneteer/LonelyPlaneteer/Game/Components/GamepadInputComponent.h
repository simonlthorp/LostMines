#pragma once

#include "../../Engine/ECS/Component.h"

#define MAX_PLAYERS 4

class GamepadInput : public Component {
public:
	SDL_GameController* gGameController = NULL;

	static int CurrentGamepadsOpen;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool a = false;
	bool x = false;

	GamepadInput() {
		CheckForAvailableGamepad();
	}

	void CheckForAvailableGamepad() {
		//Check for joysticks
		if (SDL_NumJoysticks() < 1) {
			std::cout << "Warning: No joysticks connected!" << std::endl;
		} else {
			if (CurrentGamepadsOpen == MAX_PLAYERS) {
				std::cout << "Maximum number of gamepads already open" << std::endl;
			} else {
				if (SDL_IsGameController(CurrentGamepadsOpen)) {
					gGameController = SDL_GameControllerOpen(CurrentGamepadsOpen);

					if (gGameController == NULL) {
						std::cout << "Warning: Unable to open game controller! SDL Error: " << SDL_GetError() << std::endl;
					}
					else {
						std::cout << "Opened gamepad: " << CurrentGamepadsOpen << std::endl;
						CurrentGamepadsOpen++;
					}
				} else {
					std::cout << "Gamepad could not be opened: " << CurrentGamepadsOpen << std::endl;
				}
			}
		}
	}

	~GamepadInput() {
		//close();
	}

	void update() {
		if (gGameController)
		{
			up = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_UP);
			down = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			left = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			right = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			a = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);
			x = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_X);
		}
	}

private:
	void close() {
		//Close game controller
		//SDL_JoystickClose(gGameController);
		SDL_GameControllerClose(gGameController);
		gGameController = NULL;
	}
};


