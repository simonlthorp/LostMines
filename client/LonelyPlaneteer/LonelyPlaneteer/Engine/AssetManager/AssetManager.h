#pragma once

//CPP includes
#include <string>
#include <map>
//SDL includes
#include "SDL_image.h"
#include "SDL_ttf.h"
//Engine


class AssetManager {
public:
	AssetManager();
	~AssetManager();
	void init();
	void addTexture(std::string id, const char* path);
	void addFont(std::string id, const char* path, const int fontSize);
	void removeTexture(std::string id);
	void removeFont(std::string id);
	SDL_Texture* getTexture(std::string id);
	TTF_Font* getFont(std::string id);
private:
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, SDL_Texture*> textures;
};