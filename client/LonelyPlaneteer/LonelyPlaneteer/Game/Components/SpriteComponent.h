#pragma once

#include "../../Engine/ECS/Component.h"
#include "SDL.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/AssetManager/AssetManager.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() = default;
	//Avoid doing this as its costly
	SpriteComponent(const char* textId) {
		//std::cout << "Loading Texture" << std::endl;
		texture = Game::assetManager.getTexture(textId);
		//std::cout << "Sprite Finished" << std::endl;
	}

	SpriteComponent(SDL_Texture* text) {
		//std::cout << "Loading Texture" << std::endl;
		texture = text;
		//std::cout << "Sprite Finished" << std::endl;
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void init() override {
		src.x = src.y = 0;
		src.w = entity->getComponent<TransformComponent>().width;
		src.h = entity->getComponent<TransformComponent>().height;
		culled = false;
	}

	void setDest(const float x, const float y, const int scale) {
		dest.w = src.w * scale;
		dest.h = src.h * scale;
		dest.x = static_cast<int>(x) - dest.w / 2;
		dest.y = static_cast<int>(y) - dest.h / 2;
	}
	
	SDL_Rect getDest() const {
		return dest;
	}

	SDL_Rect getSrc() const {
		return src;
	}

	SDL_Texture* getTexture() const {
		return texture;
	}

	bool getCulled() const {
		return culled;
	}

	void setTexture(SDL_Texture* tex) {
		texture = tex;
	}

	void setSrc(int x, int y) {
		src.x = x;
		src.y = y;
	}

	void setCulled(bool cull) {
		culled = cull;
	}

private:
	TransformComponent *position;
	SDL_Texture *texture;
	SDL_Rect src, dest;
	bool culled;
};