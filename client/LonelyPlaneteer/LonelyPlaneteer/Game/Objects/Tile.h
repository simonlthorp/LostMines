#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/ECS/Component.h"

class Tile : public Entity {
public:
	Tile(float x, float y, int TileType, layerLabels layer);
	void draw() override;
};
