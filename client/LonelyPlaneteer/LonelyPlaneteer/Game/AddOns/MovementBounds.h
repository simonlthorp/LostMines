#ifndef MOVEMENT_BOUNDS_H
#define MOVEMENT_BOUNDS_H

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"
#include "../../Engine/Physics/Physics.h"

class MovementBounds : public Entity
{
public:
	MovementBounds() : Entity(GameScene::manager) {};
	//Sword(float x, float y);
	MovementBounds(float x, float y, int w, int h, Entity* e);
	void collisionResponse(Collision * collision) override;
	void collisionDetected();
	void setPosition(float x, float y);
	SDL_Rect getCollider();
	bool collidesWithWall();

private:
	Entity* entity;
	int width = 50;
	int depth = 64;
	int damage = 20;
	Uint32 attackDelay = 200;
	Uint32 lastAttack = 0;

};

#endif // !MOVEMENT_BOUNDS_H