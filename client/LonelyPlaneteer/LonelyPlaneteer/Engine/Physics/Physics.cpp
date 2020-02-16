#include "Physics.h"
#include "../ECS/Component.h"
#include "../Game.h"
#include "../../Game/Classes/HeroType.h"
#include "../../Game/Enemy/Enemy.h"

bool Physics::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y) {
		return true;
	}
	return false;
}

bool Physics::collidesWithWall(const SDL_Rect& recA) {
	for (auto& e : GameScene::manager.getGroup(wallGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider)) {
			return true;
		}
	}
	return false;
}

std::string Physics::collidesWithEntity(const SDL_Rect& recA, std::string yourTag) {
	for (auto& e : GameScene::manager.getGroup(wallGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider) 
				&& e->getComponent<ColliderComponent>().tag.compare(yourTag) != 0) {
			return e->getComponent<ColliderComponent>().tag;
		}
	}
	return "";
}

Entity* Physics::collidesWithTag(const SDL_Rect& recA, std::string t) {
	for (auto& e : GameScene::manager.getGroup(wallGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider) 
				&& e->getComponent<ColliderComponent>().tag.compare(t) == 0) {
			return e;
		}
	}
	return nullptr;
}

Entity* Physics::collidesWithEnemy(const SDL_Rect& recA) {
	for (auto& e : GameScene::manager.getGroup(enemiesGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider)
			&& e->getComponent<ColliderComponent>().tag.compare("Enemy") == 0 
				&& dynamic_cast<Enemy*>(e)->getIsDead() == false) {
			return e;
		}
	}
	return nullptr;
}

Entity* Physics::collidesWithPlayer(const SDL_Rect& recA) {
	for (auto& e : GameScene::manager.getGroup(playersGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider)
			&& e->getComponent<ColliderComponent>().tag.compare("Player") == 0) {
			return e;
		}
	}
	return nullptr;
}

Entity* Physics::collidesWithOtherTeam(const SDL_Rect& recA, int team) {
	for (auto& e : GameScene::manager.getGroup(playersGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider)
			&& dynamic_cast<HeroType *>(e)->getTeam() != team  
				&& dynamic_cast<HeroType*>(e)->isRespawning() == false) {
			return e;
		}
	}
	return nullptr;
}


bool Physics::collidesWithMine(const SDL_Rect& recA) {
	for (auto& e : GameScene::manager.getGroup(mineGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider) 
			&& e->getComponent<ColliderComponent>().tag.compare("Mine") == 0) {
			return true;
		}
	}
	return false;
}


Mine* Physics::getMineOnCollision(const SDL_Rect& recA) {
	for (auto& e : GameScene::manager.getGroup(mineGroup)) {
		if (AABB(recA, e->getComponent<ColliderComponent>().collider)
			&& e->getComponent<ColliderComponent>().tag.compare("Mine") == 0) {
			return static_cast<Mine*>(e);
		}
		else {
			//std::cout << "Cannot find mine entity in getMineOnCollision" << std::endl;   // For Debugging
		}
	}
	return nullptr;
}

