#pragma once

//C++ Includes
#include <string>
//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static TTF_Font* LoadFont(const char* filename, int fontSize);
	//static void Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, double degrees);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double degrees);
	static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect dest, double degrees);
	static void Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest, double degrees);
	static void DrawFont(SDL_Texture* tex, SDL_Rect dest);
	static void DrawFont(SDL_Texture* tex, SDL_Rect* dest);
	static void DrawRect(SDL_Rect *rect);
	static void DrawRect(SDL_Rect * rect, SDL_Color col);
	static void DrawBounds(SDL_Rect * rect, SDL_Color col);
	static void DrawLine(int r, int g, int b, int tmpX, int tmpY, int goalX, int goalY);
};
