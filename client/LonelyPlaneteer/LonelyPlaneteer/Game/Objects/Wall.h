#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/ECS/Component.h"

class Wall : public Entity {
private:

public:
	Wall(SDL_Texture* texture, float x, float y);
	void update() override;

	void draw() override;

	void setPosition(float x, float y);
};
