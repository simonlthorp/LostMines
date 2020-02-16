#include "AssetManager.h"
//C++ Includes
#include <iostream>
//Engine Includes
#include "../Texture/TextureManager.h"


AssetManager::AssetManager() {}
AssetManager::~AssetManager() {}

void AssetManager::init() {
	addTexture("FireBall", "Assets/TempFireBall.png");
	addTexture("desert", "Assets/Desert.png");
	addTexture("Button", "Assets/Loading/start.png");
	addTexture("dirt", "Assets/Desert_Purple.png");
	addTexture("grass", "Assets/Desert_Purple.png");
	addTexture("water", "Assets/Desert_Purple.png");
	addTexture("tileset", "Assets/tileset.png");
	//addTexture("Knight", "Assets/Knight.png");
	addTexture("Knight", "Assets/knight_anims.png");
	addTexture("Mage", "Assets/wizard_anims.png");
	addTexture("Skeleton", "Assets/skeleton_anims.png");
	addTexture("TempSkeleton", "Assets/Skeleton.png");
	addTexture("ControlPoints", "Assets/MineSpriteSheet.png");
	//addTexture("ControlPoints", "Assets/ControlPoints.png");
	addTexture("Gems", "Assets/GemsSpriteSheet.png");
	addFont("Arial_12", "Assets/Fonts/arial.ttf", 12);
	addFont("Arial_13", "Assets/Fonts/arial.ttf", 13);
	addFont("Arial_14", "Assets/Fonts/arial.ttf", 14);
	addFont("Arial_15", "Assets/Fonts/arial.ttf", 15);
	addFont("Arialbd_20", "Assets/Fonts/arialbd.ttf", 20);
	addFont("Arialbd_30", "Assets/Fonts/arialbd.ttf", 30);
	addFont("Arialbd_40", "Assets/Fonts/arialbd.ttf", 40);
	addFont("Arialbd_64", "Assets/Fonts/arialbd.ttf", 64);

	addTexture("circle1", "Assets/Loading/circle1.png");
	addTexture("circle2", "Assets/Loading/circle2.png");
	addTexture("circle3", "Assets/Loading/circle3.png");
	addTexture("circle4", "Assets/Loading/circle4.png");
	addTexture("circle5", "Assets/Loading/circle5.png");
	addTexture("circle6", "Assets/Loading/circle6.png");
	addTexture("circle7", "Assets/Loading/circle7.png");
	addTexture("circle8", "Assets/Loading/circle8.png");
	addTexture("circle9", "Assets/Loading/circle9.png");
	addTexture("circle10", "Assets/Loading/circle10.png");
	addTexture("circle11", "Assets/Loading/circle11.png");
	addTexture("loadBackground", "Assets/Loading/Background.png");
	addTexture("wallpaper1", "Assets/wallpaper1.png");
	addTexture("wallpaper2", "Assets/wallpaper2.png");
	addTexture("wallpaper3", "Assets/wallpaper3.png");
	addTexture("wallpaper4", "Assets/wallpaper4.png");
	addTexture("black", "Assets/black.png");
	addTexture("black_lowalpha", "Assets/black_lowalpha.png");

	//Emblem
	addTexture("red", "Assets/red.png");
	addTexture("blue", "Assets/blue.png");
	addTexture("emblem_empty", "Assets/Emblem/healthbarEmpty.png");
	addTexture("emblem_red", "Assets/Emblem/healthred.png");
	addTexture("emblem_blue", "Assets/Emblem/healthblue.png");
}

void AssetManager::addTexture(std::string id, const char* path) {
	SDL_Texture* tmp = TextureManager::LoadTexture(path);
	textures.emplace(id, tmp);
	//std::cout << "Created Texture: " << id << std::endl;
}

void AssetManager::addFont(std::string id, const char* path, const int fontSize) {
	TTF_Font* tmp = TextureManager::LoadFont(path, fontSize);
	fonts.emplace(id, tmp);
	//std::cout << "Created Font: " << id << std::endl;
}

void AssetManager::removeTexture(std::string id) {
	if (textures.find(id) != textures.end()) {
		//found
		textures.erase(id);
	}
	else {
		//std::cout << "Failed to remove texture" << std::endl;
	}
}

void AssetManager::removeFont(std::string id) {
	if (fonts.find(id) != fonts.end()) {
		//found
		fonts.erase(id);
	}
	else {
		//std::cout << "Failed to remove font" << std::endl;
	}
}

SDL_Texture* AssetManager::getTexture(std::string id) {
	return textures[id];
}

TTF_Font* AssetManager::getFont(std::string id) {
	return fonts[id];
}