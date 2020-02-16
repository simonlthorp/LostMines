#ifndef MOB_AREA_H
#define MOB_AREA_H

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"
#include "../Map/RespawnPoint.h"
class MobArea : public Entity {
private:
	RespawnPoint respawnPoint;
	int weight = 0;
	int topLeftX;
	int topLeftY;
	int btmRightX;
	int btmRightY;
public:

	MobArea(float x, float y, int w, int h);

	int getSpawnX() { return respawnPoint.getX(); };
	int getSpawnY() { return respawnPoint.getY(); };
	RespawnPoint getRespawnPoint() { return respawnPoint; };
	void increaseWeight() { weight++; };
	void update() override;
	void draw() override;
};
#endif // !MOB_AREA_H

#pragma once
