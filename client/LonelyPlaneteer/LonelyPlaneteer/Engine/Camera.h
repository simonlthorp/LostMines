#pragma once
#include "SDL.h"

class Camera {
private:
	SDL_Rect rect;
public:
	Camera(int posX, int posY, int width, int height);
};
