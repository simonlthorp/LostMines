#pragma once

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"
#include "../../Engine/Physics/Physics.h"

class Sword : public Entity
{
public:
	Sword();
	//Sword(float x, float y);
	Sword(float x, float y, Entity* h);
	void collisionDetected();
	void updatePosition(int x, int y, bool facingUpDown);
	void setPosition(float x, float y);
	void attackPosition(int x, int y);
	void collisionResponse(Collision* collision) override;

private:
	Entity* thisHero;
	int width = 50;
	int depth = 64;
	int damage = 20;
	Uint32 attackDelay = 600;
	Uint32 lastAttack = 0;

};
