#include "TextureManager.h"
//C++ Includes
#include <mutex>
//Engine Includes
#include "../Game.h"
#include "../Camera.h"


SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	Game::rendering.lock();

	//std::cout << "Loading Image: " << filename << std::endl;
	SDL_Surface* tempSurface = IMG_Load(filename);
	if (!tempSurface) {
		printf("******************ERROR IMG_Load: %s\n", IMG_GetError());
	}
	//std::cout << "Creating Texture From Surface" << std::endl;
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//std::cout << "Freeing Surface" << std::endl;
	SDL_FreeSurface(tempSurface);
	//std::cout << "Returning Texture" << std::endl;
	Game::rendering.unlock();
	return tex;
}

TTF_Font* TextureManager::LoadFont(const char* filename, int fontSize) {
	Game::rendering.lock();

	//std::cout << "Loading Font: " << filename << std::endl;

	TTF_Font* tempText = TTF_OpenFont(filename, fontSize);
	if (!tempText) {
		printf("******************ERROR IMG_Load: %s\n", TTF_GetError());
	}
	Game::rendering.unlock();
	return tempText;
}

/*void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest, double degrees)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, degrees, NULL, SDL_FLIP_NONE);
}*/

//Possible Critical Section
//std::mutex loadingPath;
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double degrees) {
	//loadingPath.lock();
	SDL_Rect destination = { dest.x - Game::camera.x, dest.y - Game::camera.y, dest.w, dest.h };
	//SDL_RenderCopyEX(Game::renderer, tex, NULL, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, &src, &destination, degrees, NULL, SDL_FLIP_NONE);
	//loadingPath.unlock();
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect dest, double degrees) {
	//loadingPath.lock();
	SDL_Rect destination = { dest.x - Game::camera.x, dest.y - Game::camera.y, dest.w, dest.h };
	//SDL_RenderCopyEX(Game::renderer, tex, NULL, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, src, &destination, degrees, NULL, SDL_FLIP_NONE);
	//loadingPath.unlock();
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dest, double degrees) {
	//loadingPath.lock();
	SDL_Rect destination = { dest->x - Game::camera.x, dest->y - Game::camera.y, dest->w, dest->h };
	//SDL_RenderCopyEX(Game::renderer, tex, NULL, &dest);
	SDL_RenderCopyEx(Game::renderer, tex, src, &destination, degrees, NULL, SDL_FLIP_NONE);
	//loadingPath.unlock();
}

void TextureManager::DrawFont(SDL_Texture* tex, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}

void TextureManager::DrawFont(SDL_Texture* tex, SDL_Rect* dest) {
	SDL_RenderCopy(Game::renderer, tex, NULL, dest);
}


void TextureManager::DrawRect(SDL_Rect* rect) {
	SDL_Rect destination = { rect->x - Game::camera.x, rect->y - Game::camera.y, rect->w, rect->h };
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(Game::renderer, &destination);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

void TextureManager::DrawRect(SDL_Rect* rect, SDL_Color col) {
	SDL_Rect destination = { rect->x - Game::camera.x, rect->y - Game::camera.y, rect->w, rect->h };

	SDL_SetRenderDrawColor(Game::renderer, col.r, col.g, col.b, col.a);
	SDL_RenderFillRect(Game::renderer, &destination);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

void TextureManager::DrawBounds(SDL_Rect* rect, SDL_Color col) {

	SDL_Rect destination = { rect->x - Game::camera.x, rect->y - Game::camera.y, rect->w, rect->h };

	SDL_SetRenderDrawColor(Game::renderer, col.r, col.g, col.b, col.a);
	SDL_RenderDrawRect(Game::renderer, &destination);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

void TextureManager::DrawLine(int r, int g, int b, int tmpX, int tmpY, int goalX, int goalY) {
	/*SDL_SetRenderDrawColor(Game::renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(Game::renderer, tmpX - Game::camera.x, tmpY - Game::camera.y, 
			goalX - Game::camera.x, goalY - Game::camera.y);
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);*/
}