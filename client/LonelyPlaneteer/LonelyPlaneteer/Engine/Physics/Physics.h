#pragma once
#include "SDL.h"
#include "../../Game/Objects/Wall.h"
#include "../ECS/ECS.h"
#include "../../Game/Objects/Mine.h"
#include <memory>

class Physics {

public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool collidesWithWall(const SDL_Rect& recA);
	static std::string collidesWithEntity(const SDL_Rect& recA, std::string yourTag);
	static Entity* collidesWithTag(const SDL_Rect& recA, std::string t);
	static Entity* collidesWithEnemy(const SDL_Rect& recA);
	static Entity* collidesWithPlayer(const SDL_Rect& recA);
	static bool collidesWithMine(const SDL_Rect& recA);
	static Mine* getMineOnCollision(const SDL_Rect& recA);
	static Entity* collidesWithOtherTeam(const SDL_Rect& recA, int team);
};