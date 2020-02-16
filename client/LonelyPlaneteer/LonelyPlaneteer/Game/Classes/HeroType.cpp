#include "HeroType.h"
#include <iostream>
#include "../../Engine/Physics/Collision.h"
#include "../Objects/Player.h"


HeroType::HeroType() : Entity(GameScene::manager) {}

void HeroType::draw() {
	SDL_Color borderColor = { 0, 0, 0};
	SDL_Color healthColor = { 0, 255, 0 };

	if (team == 1) {
		borderColor = { 255, 0, 0 };
	} else {
		borderColor = { 0, 0, 255 };
	}

	SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();
	SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();
	SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture();
	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
		
	if (!isRespawning()) {
		//The Movement Collider
		//TextureManager::DrawRect(&movementB->getCollider(), { 0,0,255 });


		TextureManager::DrawRect(&this->getComponent<HealthComponent>().border, borderColor);
		TextureManager::DrawRect(&this->getComponent<HealthComponent>().healthBar, healthColor);
		TextureManager::Draw(tex, src, dest, 0);

	} else if (isRespawning() && ((SDL_GetTicks() - timeOfDeath) < animator->getAnimation(animator->getCurrent()).numberOfFrames * animator->getAnimation(animator->getCurrent()).msPerFrame)) {
		TextureManager::Draw(tex, src, dest, 0);
	}
}

void HeroType::update() {
	if (!isPlayer) {
		if (!isRespawning()) {
			updatePosition();
			updateAnimation();
		} else {
			updateAnimation();
			respawn();
		}
	}

	isCollidingWithMine = false;


	//std::cout << this->getComponent<TransformComponent>().position.x << ", " << this->getComponent<TransformComponent>().position.y << std::endl;
}

void HeroType::updateHero() {
	int t = static_cast<int>(SDL_GetTicks());
	int animationLength = timeOfDeath + (animator->getAnimation(animator->getCurrent()).numberOfFrames * animator->getAnimation(animator->getCurrent()).msPerFrame);
	int nof = animator->getAnimation(animator->getCurrent()).numberOfFrames;
	int mspf = animator->getAnimation(animator->getCurrent()).msPerFrame;
	if (!isRespawning()) {
		updatePosition();
		updateAnimation();
	} else {
		updateAnimation();
		if (t > animationLength) {
			
			respawn();
		}
		
		
	}
	isCollidingWithMine = false;
}

void HeroType::lateUpdate() {
	if (isPlayer) {

		//if (!player->getEKeyPressed()) {
		//	if (!mineStack.empty()) {
		//		mineStack.top()->stopAnimating(this);
		//	}
		//}

		if (!isCollidingWithMine || !player->getEKeyPressed()) {
			hasStartedMining = false;
			if (!mineStack.empty()) {
				mineStack.top()->stopAnimating(*this);
				mineStack.top()->setCurrentlyMining(false);
				mineStack.pop();
			}
		}
	}
}

void HeroType::updatePosition() {
	TransformComponent tc = this->getComponent<TransformComponent>();
	SDL_Rect spriteRect = this->getComponent<SpriteComponent>().getDest();

	float x = tc.position.x;
	float y = tc.position.y;

	x += tc.velocity.x * tc.speed;
	y += tc.velocity.y * tc.speed;
	if (tc.velocity.x == 0 && tc.velocity.y == 0) {
		//setStateTo(0);
	} else {
		//setStateTo(1);
	}

	if (!isRespawning()) {
		this->getComponent<TransformComponent>().setPos(x, y);
		this->getComponent<SpriteComponent>().setDest(x, y, tc.scale);

		//update the collider
		this->getComponent<ColliderComponent>().setCollider(x, y);

		this->getComponent<HealthComponent>().setPosition(spriteRect.x, spriteRect.y, spriteRect.w, spriteRect.h);

		movementB->setPosition(x, y);
		if (!type) {
			
			updateSwordPosition();
		}
	}
}

bool HeroType::seeIfPlayerCanMine() {
	if (currentMine != nullptr) {
		if (currentMine->canPlayerMine(type))
			return true;
		else return false;
	} else {
		std::cout << "mineEntity from getMineOnCollision is a NULL PTR" << std::endl;
		return false;
	}

}

void HeroType::startMining() {
	if (!isRespawning()) {
		if (currentMine != nullptr) {
			float points = currentMine->mineResources(*this);
			// ADD TO SCORE
			addToScore(points);
		}
		else {
			std::cout << "mineEntity from getMineOnCollision is a NULL PTR" << std::endl;
		}
	}
}

// Set the time of the "E" key being pressed down (in milliseconds)
//void HeroType::setMineKeyTime(Uint32 keyTime) {
//	if (currentMine != nullptr) {
//		currentMine->setKeyPressTime(keyTime);
//	}
//	else {
//		std::cout << "mineEntity from getMineOnCollision is a NULL PTR" << std::endl;
//	}
//}


void HeroType::collisionResponse(Collision* collision) {
	currentMine = nullptr;

	switch (collision->type) {
		case CollisionType::movement_mine: {
			currentMine = static_cast<Mine*>(collision->other.get());
			if (!isCollidingWithMine)
				mineStack.push(currentMine);

			isCollidingWithMine = true;

			if (isPlayer) {
				if (player->getEKeyPressed()) {
					if (seeIfPlayerCanMine()) {
						// get the very first timestamp of the key being pressed down.
						if (!hasStartedMining) {
							Uint32 keyTime = SDL_GetTicks();
							//setMineKeyTime(keyTime);
							hasStartedMining = true;
						}
						startMining();
					}
				}
				else {
					currentMine->setCurrentlyMining(false);
				}
			}
			break;
		}
		default:
			break;
	}
}

void HeroType::updateVelocityY(float y) {
	this->getComponent<TransformComponent>().velocity.y = y;
}

void HeroType::updateVelocityX(float x) {
	this->getComponent<TransformComponent>().velocity.x = x;
}

void HeroType::updateAnimation() {

	int time = SDL_GetTicks();

	if (isAttacking) {
		//Begin Animation at 0 ticks from the time the attack starts
		this->getComponent<SpriteComponent>().setSrc(
			this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>(((SDL_GetTicks()-attackTime) / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
			animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
		
    	if (time > attackTime + attackLength) {
			//End attack animation
			setIdleAnim();
			isAttacking = false;
		}
	}
	else if (isRespawning()) {
		//Update death animation with respawn time
		this->getComponent<SpriteComponent>().setSrc(
			this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>(((SDL_GetTicks() - timeOfDeath) / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
			animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
	}
	else
	{
		//Update animation using number of microseconds in game
		this->getComponent<SpriteComponent>().setSrc(
			this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>((SDL_GetTicks() / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
			animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
	}

}

void HeroType::changeAnimation(const char* animName) {
	animator->playAnimation(animName);
}

void HeroType::attack() {
	if (type) {
		//WIZARD ATTACK
		if (!isRespawning()) {
			shootProjectile();
		}
	} else {
		//KNIGHT ATTACK
		//std::cout << "KNIGHT ATTACK" << std::endl;
	}
}

// Resets the player's score to 0
void HeroType::resetScore() {
	 heroScore = 0;
}

void HeroType::setDirection(int direction) {
	this->facingDirection = direction;
}

int HeroType::getDirection() {
	return facingDirection;
}

unsigned int HeroType::getType() {
	return type;
}

void HeroType::setIdleAnim() {

	switch (getDirection())
	{
	case HeroType::directions::UP:
		animator->playAnimation("idleUp");
		break;
	case HeroType::directions::DOWN:
		animator->playAnimation("idleDown");
		break;
	case HeroType::directions::LEFT:
		animator->playAnimation("idleLeft");
		break;
	case HeroType::directions::RIGHT:
		animator->playAnimation("idleRight");
		break;
	default:
		animator->playAnimation("idleDown");
		break;
	}

}

void HeroType::attackAnim() {

	switch (facingDirection)
	{
	case directions::UP:
		animator->playAnimation("attackUp");
		break;
	case directions::DOWN:
		animator->playAnimation("attackDown");
		break;
	case directions::LEFT:
		animator->playAnimation("attackLeft");
		break;
	case directions::RIGHT:
		animator->playAnimation("attackRight");
		break;
	default:
		break;
	}
	
}

bool HeroType::getIsAttacking() {
	return isAttacking;
}

Sword* HeroType::getSword() {
	return sword;
}

void HeroType::takeDamage(int dmg) {
	this->getComponent<HealthComponent>().damageHealth(dmg);
	if (this->getComponent<HealthComponent>().getHealth() <= 0 && !respawning) {
		die();
	}
}

//Kills the player
void HeroType::die() {
	respawning = true;
	timeOfDeath = SDL_GetTicks();
	animator->playAnimation("death");
	Game::mixer->playRandomSound(AudioMixer::playerDeathSounds);
	
	
}

int HeroType::getAttackDamage() {
	return this->getComponent<CombatComponent>().getDamage();
}

void HeroType::updateSwordPosition() {
	TransformComponent tc = this->getComponent<TransformComponent>();
	ColliderComponent cc = this->getComponent<ColliderComponent>();
	int x = static_cast<int>(tc.position.x);
	int y = static_cast<int>(tc.position.y);
	bool facingUpDown = true;
	switch (facingDirection) {
		case directions::UP:
			//sword->updatePosition(tc.position.x, tc.position.y + )
			y -= cc.collider.h / 2;
			facingUpDown = true;
			break;
		case directions::DOWN:
			y += cc.collider.h;
			facingUpDown = true;
			break;
		case directions::LEFT:
			x -= cc.collider.w;
			facingUpDown = false;
			break;
		case directions::RIGHT:
			x += cc.collider.w;
			facingUpDown = false;
			break;
		default:
			break;
	}
	sword->updatePosition(x, y, facingUpDown);
}

bool HeroType::isRespawning() {
	return respawning;
}

void HeroType::respawn() {
	if (SDL_GetTicks() > respawnTime + timeOfDeath) {
		this->getComponent<TransformComponent>().setPos(static_cast<float>(respawnPoint.getX()), static_cast<float>(respawnPoint.getY()));
		this->getComponent<HealthComponent>().resetHealth();
		respawning = false;
		animator->playAnimation("idleDown");
	}
}

void HeroType::shootProjectile() {

	float x = this->getComponent<TransformComponent>().position.x;
	float y = this->getComponent<TransformComponent>().position.y;
	int direction = 0;
	switch (facingDirection) {
	case directions::UP:
		direction = 1;
		break;
	case directions::DOWN:
		direction = 2;
		break;
	case directions::LEFT:
		direction = 3;
		break;
	case directions::RIGHT:
		direction = 4;
		break;
	default:
		break;
	}

	if (SDL_GetTicks() > lastShot + fireRate) {
		Projectile* fireball = new Projectile(x, y, direction, team);

		lastShot = SDL_GetTicks();
	}

}
