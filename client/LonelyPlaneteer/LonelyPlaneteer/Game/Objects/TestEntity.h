#pragma once

//#include "../../Engine/ECS/ECS.h"
#include "../Scene/GameScene.h"
#include "../Map/MapManager.h"

//#define MAP_WIDTH 960
//#define MAP_HEIGHT 640
#define MAP_WIDTH 1200
#define MAP_HEIGHT 700

class TestEntity : public Entity {
private:
	float goalX, goalY;

	const static int midX = MAP_WIDTH / 2;
	const static int midY = MAP_HEIGHT / 2;

	SDL_Color color;

public:
	TestEntity(float x, float y);

	void update() override;

	void draw() override;

	void collisionResponse(Collision* collision) override;

	void SetColliderColor(int r, int g, int b, int a);

	void updatePosition();

	void move();

	void setPosition(float x, float y);

	void wander();

};