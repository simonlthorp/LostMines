#pragma once
//part of screen
#include "Camera.h"

Camera::Camera(int posX, int posY, int width, int height) {
	rect = { posX, posY, width, height };
	//cameraRect = {0,0,800,600 };
}

