#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Component.h"
#include "Collision.h"

class CollisionManager
{
public:
	//CollisionManager();
	//~CollisionManager();

	static void handleCollision(std::unique_ptr<Entity>& a, std::unique_ptr<Entity>& b);
};