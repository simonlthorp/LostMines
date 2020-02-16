#include "Wizard.h"

Wizard::Wizard(int t) : HeroType() {
	SDL_Rect spriteDest;
	if (t == 1) {
		respawnPoint = RespawnPoint(250, 250);
	} else {
		respawnPoint = RespawnPoint(1800, 900);
	}

	int x = respawnPoint.getX();
	int y = respawnPoint.getY();

	movementB = new MovementBounds(static_cast<float>(x), static_cast<float>(y), 64, 64, this);

	this->addComponent<TransformComponent>(static_cast<float>(x), static_cast<float>(y), 64, 64, 1);
	this->getComponent<TransformComponent>().setSpeed(3);

	this->addComponent<SpriteComponent>(spriteStr);
	this->getComponent<SpriteComponent>().setSrc(0, 0);
	this->getComponent<SpriteComponent>().setDest(static_cast<const float>(x), static_cast<const float>(y), 1);

	spriteDest = this->getComponent<SpriteComponent>().getDest();

	this->addComponent<ColliderComponent>("Player");
	this->getComponent<ColliderComponent>().setColliderSize(40, 50);

	this->getComponent<ColliderComponent>().setCollider(static_cast<float>(x), static_cast<float>(y));

	this->addComponent<HealthComponent>(100);

	this->getComponent<HealthComponent>().setPosition(spriteDest.x, spriteDest.y,
		spriteDest.w, spriteDest.h);

	this->addComponent<CombatComponent>(10);

	this->setLayer(topLayer);
	this->addGroup(playersGroup);
	type = 1;
	team = t;

	animator = new Animator();
	animator->addAnimation("idleUp", Animation(0, 1, 100));
	animator->addAnimation("idleLeft", Animation(1, 1, 100));
	animator->addAnimation("idleDown", Animation(2, 1, 100));
	animator->addAnimation("idleRight", Animation(3, 1, 100));
	animator->addAnimation("castUp", Animation(4, 9, 75));
	animator->addAnimation("castLeft", Animation(5, 9, 75));
	animator->addAnimation("castDown", Animation(6, 9, 75));
	animator->addAnimation("castRight", Animation(7, 9, 75));
	animator->addAnimation("walkUp", Animation(8, 5, 50));
	animator->addAnimation("walkLeft", Animation(9, 5, 50));
	animator->addAnimation("walkDown", Animation(10, 5, 50));
	animator->addAnimation("walkRight", Animation(11, 5, 50));
	animator->addAnimation("attackUp", Animation(12, 5, 100));
	animator->addAnimation("attackLeft", Animation(13, 5, 100));
	animator->addAnimation("attackDown", Animation(14, 5, 100));
	animator->addAnimation("attackRight", Animation(15, 5, 100));
	animator->addAnimation("death", Animation(16, 6, 100));

	animator->playAnimation("idleDown");
	facingDirection = directions::DOWN;

	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);
}

void Wizard::playAttackAnimation() {
	//std::cout << "ATTACK KNIGHT" << std::endl;
	attackAnim();

	//Get the length of the attack animation
	attackLength = animator->getAnimation(animator->getCurrent()).msPerFrame * animator->getAnimation(animator->getCurrent()).numberOfFrames;
	//Get the time the attack was initiated
	if (!isAttacking) {
		attackTime = SDL_GetTicks();
		Game::mixer->fireball->play();
	}

	//Set Knight as attacking
	isAttacking = true;
}