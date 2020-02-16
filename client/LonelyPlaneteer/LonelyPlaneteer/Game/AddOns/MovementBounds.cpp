#include "MovementBounds.h"
#include "../../Engine/Physics/Collision.h"
#include "../Classes/HeroType.h"

MovementBounds::MovementBounds(float x, float y, int w, int h, Entity* e) : Entity(GameScene::manager) {
	entity = e;

	this->addComponent<TransformComponent>(static_cast<float>(x), static_cast<float>(y), w, h, 1);

	this->addComponent<ColliderComponent>("Movement");
	this->getComponent<ColliderComponent>().setColliderSize(30, 15);
	this->getComponent<ColliderComponent>().setColliderPosition(static_cast<int>(x), static_cast<int>(y), 2, 1);

	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);

	GameScene::manager.addNewEntity(this);
}

void MovementBounds::collisionResponse(Collision* collision) {
	switch (collision->type) {
		case CollisionType::movement_wall: {
			HeroType* player = dynamic_cast<HeroType*>(entity);
			player->getComponent<TransformComponent>().velocity * -1;
			player->updatePosition();
			break;
		}
		case CollisionType::movement_mine: {
			HeroType* player = dynamic_cast<HeroType*>(entity);
			player->collisionResponse(collision);
			break;
		}
		default:
			break;
	}
}

void MovementBounds::collisionDetected() {

}


void MovementBounds::setPosition(float x, float y) {
	this->getComponent<TransformComponent>().setPos(x, y);

	this->getComponent<ColliderComponent>().setColliderPosition(static_cast<int>(x), static_cast<int>(y), 2, 1);
}

SDL_Rect MovementBounds::getCollider() {
	return this->getComponent<ColliderComponent>().collider;
}

//******************************REPLACE WITH QUAD TREE STUFF
bool MovementBounds::collidesWithWall() {
	return Physics::collidesWithWall(this->getComponent<ColliderComponent>().collider);
}



