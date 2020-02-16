#include "Knight.h"

Knight::Knight(int t) : HeroType() {
	SDL_Rect spriteDest;
	if (t == 1) {
		respawnPoint = RespawnPoint(120, 100);
	} else {
		respawnPoint = RespawnPoint(1650, 800);
	}

	int x = respawnPoint.getX();
	int y = respawnPoint.getY();

	movementB = new MovementBounds(static_cast<float>(x), static_cast<float>(y), 192, 192, this);

	this->addComponent<TransformComponent>(static_cast<float>(x), static_cast<float>(y), 192, 192, 1);
	this->getComponent<TransformComponent>().setSpeed(3);


	this->addComponent<SpriteComponent>(spriteStr);
	this->getComponent<SpriteComponent>().setSrc(0, 0);
	this->getComponent<SpriteComponent>().setDest(static_cast<const float>(x), static_cast<const float>(y), 1);
	
	spriteDest = this->getComponent<SpriteComponent>().getDest();

	this->addComponent<ColliderComponent>("Player");
	this->getComponent<ColliderComponent>().setColliderSize(40, 47);
	this->getComponent<ColliderComponent>().setCollider(static_cast<float>(x), static_cast<float>(y));

	sword = new Sword(static_cast<float>(x), static_cast<float>(y), this);

	this->addComponent<HealthComponent>(100);

	this->addComponent<CombatComponent>(20);

	this->setLayer(topLayer);
	//this->setLayer(layer8);
	this->addGroup(playersGroup);
	type = 0;
	team = t;

	animator = new Animator();
	animator->addAnimation("idleUp", Animation(0, 1, 100));
	animator->addAnimation("idleLeft", Animation(1, 1, 100));
	animator->addAnimation("idleDown", Animation(2, 1, 100));
	animator->addAnimation("idleRight", Animation(3, 1, 100));
	animator->addAnimation("walkUp", Animation(4, 9, 75));
	animator->addAnimation("walkLeft", Animation(5, 9, 75));
	animator->addAnimation("walkDown", Animation(6, 9, 75));
	animator->addAnimation("walkRight", Animation(7, 9, 75));
	animator->addAnimation("attackUp", Animation(8, 6, 100));
	animator->addAnimation("attackLeft", Animation(9, 6, 100));
	animator->addAnimation("attackDown", Animation(10, 6, 100));
	animator->addAnimation("attackRight", Animation(11, 6, 100));
	animator->addAnimation("death", Animation(12, 6, 100));

	animator->playAnimation("idleDown");
	facingDirection = directions::DOWN;

	this->getComponent<HealthComponent>().setPosition(spriteDest.x, spriteDest.y, 
			spriteDest.w, spriteDest.h);

	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);
}

void Knight::playAttackAnimation() {
	//std::cout << "ATTACK KNIGHT" << std::endl;
	attackAnim();

	//Get the length of the attack animation
	attackLength = animator->getAnimation(animator->getCurrent()).msPerFrame * animator->getAnimation(animator->getCurrent()).numberOfFrames;
	//Get the time the attack was initiated
	if (!isAttacking) {
		attackTime = SDL_GetTicks();
		Game::mixer->playRandomSound(AudioMixer::whooshSounds);
	}
	
	//Set Knight as attacking
	isAttacking = true;


}

Sword* Knight::getSword() {
	return sword;
}
