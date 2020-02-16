#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"
#include <map>
//#include "Animation.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/Physics/Physics.h"
//#include "Enemy.h"

class Projectile : public Entity
{
public:
	Projectile();
	Projectile(float x, float y, int Direction, int t);
	~Projectile();

	void update() override;

	void updatePosition();

	void draw() override;

	void play(const char* animName);

	void collisionResponse(Collision* collision) override;

	void killBullet();

private:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	int frames = 0;
	int animSpeed = 0;
	float bulletSpeed = 6.0f;
	int origin_x;
	int origin_y;
	Uint32 hitTime = 0;
	int range = 300;
	int distTravelled = 0;
	int direction;
	double angle = 0.0;
	int team = 0;
	bool bulletDead = false;
	int damage = 30;
};
