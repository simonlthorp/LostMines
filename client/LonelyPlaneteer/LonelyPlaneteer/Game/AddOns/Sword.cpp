
#include "Sword.h"
#include "../../Game/Enemy/Enemy.h"
#include "../../Engine/Physics/Collision.h"

Sword::Sword() : Entity(GameScene::manager) {}

Sword::Sword(float x, float y, Entity * h): Entity(GameScene::manager) {
	thisHero = h;
	this->addComponent<TransformComponent>(x, y);
	this->addComponent<ColliderComponent>("Sword");
	this->getComponent<ColliderComponent>().setColliderSize(width, depth);
	GameScene::manager.addNewEntity(this);
	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);
}

void Sword::collisionDetected() {

}

void Sword::updatePosition(int x, int y, bool facingUpDown) {
	TransformComponent tc = this->getComponent<TransformComponent>();

	this->getComponent<TransformComponent>().setPos(static_cast<float>(x), static_cast<float>(y));
	this->getComponent<ColliderComponent>().setCollider(static_cast<float>(x), static_cast<float>(y));

	//changes collider size based on direction that the knight is facing
	if (facingUpDown) {
		this->getComponent<ColliderComponent>().setColliderSize(width, depth);
	} else {
		this->getComponent<ColliderComponent>().setColliderSize(depth, width);
	}
}

void Sword::setPosition(float x, float y) {
	TransformComponent tc = this->getComponent<TransformComponent>();

	this->getComponent<TransformComponent>().setPos(x, y);
	this->getComponent<ColliderComponent>().setCollider(x, y);
}


void Sword::attackPosition(int x, int y) {

	TransformComponent tc = this->getComponent<TransformComponent>();
	float tcx = tc.position.x;
	float tcy = tc.position.y;

	this->getComponent<TransformComponent>().setPos(tcx + x, tcy + y);

	//update the collider
	this->getComponent<ColliderComponent>().setCollider(tcx + x, tcy + y);

}

void Sword::collisionResponse(Collision* collision) {
		switch (collision->type) {
			case CollisionType::sword_player: {
				HeroType* hero = dynamic_cast<HeroType*>(collision->other.get());
				HeroType* thisHeroType = dynamic_cast<HeroType*>(thisHero);
				
				if (thisHeroType->getIsPlayer() && !thisHeroType->isRespawning())
				{
					if (hero->getTeam() != thisHeroType->getTeam()) {
						if (thisHeroType->getPlayer()->getSpacebarPressed())
						{
							if (SDL_GetTicks() > lastAttack + attackDelay) {
								Game::mixer->playRandomSound(AudioMixer::swordPlayerImpactSounds);
								hero->takeDamage(damage);
								lastAttack = SDL_GetTicks();

							}
						}
					}
				}

				break;
			}
			case CollisionType::sword_enemy: {
				Enemy* enemy = dynamic_cast<Enemy*>(collision->other.get());
				HeroType* thisHeroType = dynamic_cast<HeroType*>(thisHero);
				
				if (thisHeroType->getIsPlayer())
				{
						if (thisHeroType->getPlayer()->getSpacebarPressed())
						{
							if (SDL_GetTicks() > lastAttack + attackDelay) {

								enemy->takeDamage(damage);
								lastAttack = SDL_GetTicks();
								//thisHeroType->addToScore(1.0f); //give 1 point to player's team for killing enemy

							}
						}
				}
				break;
			}
			default:
				break;
		}
}
