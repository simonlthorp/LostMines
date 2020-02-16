#include "CollisionManager.h"
#include "../../Game/Classes/HeroType.h"
#include "../../Game/Objects/Player.h"

void CollisionManager::handleCollision(std::unique_ptr<Entity>& a, std::unique_ptr<Entity>& b) {
	ColliderComponent & colA = a->getComponent<ColliderComponent>();
	ColliderComponent & colB = b->getComponent<ColliderComponent>();

	//if (colA.tag.compare("Player") == 0) {
	//	if (colB.tag.compare("Wall") == 0) {
	//		a->collisionResponse(new Collision{ b, CollisionType::player_wall });
	//		return;
	//	}
	//} else if (colA.tag.compare("Test Entity") == 0) {
	//	if (colB.tag.compare("Test Entity") == 0) {
	//		a->collisionResponse(nullptr);
	//		return;
	//	}
	//}
	//else
	if (colA.tag.compare("FireBall") == 0) {
		if (colB.tag.compare("Player") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::fireball_player });
			return;
		} else if (colB.tag.compare("Enemy") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::fireball_enemy });
			return;
		} else if (colB.tag.compare("FireballWall") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::fireball_wall });
			return;
		}
	}
	else if (colA.tag.compare("Sword") == 0) {
		if (colB.tag.compare("Player") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::sword_player });
			return;
		} else if (colB.tag.compare("Enemy") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::sword_enemy });
			return;
		}
	}
	else if (colA.tag.compare("Movement") == 0) {
		if (colB.tag.compare("Wall") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::movement_wall });
			return;
		} else if (colB.tag.compare("Mine") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::movement_mine });
			return;
		}
	}
	else if (colA.tag.compare("Mine") == 0) {
		if (colB.tag.compare("Player") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::mine_player });
			return;
		}
		else if (colB.tag.compare("Movement") == 0) {
			a->collisionResponse(new Collision{ b, CollisionType::mine_player });
			return;
		}
	}
}
 