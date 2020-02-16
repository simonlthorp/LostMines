#include "Player.h"
#include "../Scene/GameScene.h"
#include "../AddOns/Sword.h"

Player::Player(HeroType* c, bool isLocal) : Entity(GameScene::manager), local(isLocal) {
	plyrClass = std::unique_ptr<HeroType>(c);
	
	plyrClass->setToPlayer();
	this->addComponent<Input>();
	this->addComponent<GamepadInput>();

	lastShot = SDL_GetTicks();

	c->setPlayer(this);

	//Animation walk = Animation(0, 8, 100);
	//Animation idle = Animation(1, 4, 700);

	//animations.emplace("Walk", walk);
	//animations.emplace("Idle", idle);
	//animate();
}

TransformComponent & Player::getTransformComponent()
{
	return this->plyrClass->getComponent<TransformComponent>();
}

void Player::play(const char* animName) {

	//frames = animations[animName].frames;
	//animIndex = animations[animName].index;
	//speed = animations[animName].speed;

}

void Player::eventHandle() {
	//Movement
	//this->getComponent<GamepadInput>().update();
	//this->getComponent<Input>().update();
	//move();
	//actions();
	//attack();
	//Mouse control
	//MouseController mc = this->getComponent<MouseController>();
	//mc.update();
	//if (mc.shooting) {
//		shoot(mc.getMouseX(), mc.getMouseY());
//	}
	
}

void Player::update() {
	//attack();
	/*this->getComponent<SpriteComponent>().setSrc(
		this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>((SDL_GetTicks() / speed) % frames),
		animIndex * this->getComponent<TransformComponent>().height
	);*/


	getInput();

	move();
	actions();
	attack();

	plyrClass->updateHero();
	//animate();

	//this->getComponent<GamepadInput>().update();



}

//draws player's sprite
void Player::draw() { 
	if (!plyrClass->isRespawning()) {
		//plyrClass->draw();
	}
}

//updates player's position based on velocity
void Player::updatePosition() {
	plyrClass->updatePosition();
}

void Player::updateAnimation() {
	plyrClass->updateAnimation();
}

void Player::setStateTo(const int s) {
	state = s;
}

void Player::animate() {
	/*switch (state) {
		case 0:
			play("Idle");
			break;
		case 1:
			play("Walk");
			break;
		default:
			play("Idle");
			break;
	}*/
}


void Player::getInput() {
	if (local) {
		GamepadInput& gamepadInput = this->getComponent<GamepadInput>();
		gamepadInput.update();
		if (gamepadInput.x) {
			eKeyPressed = true;
		} else {
			eKeyPressed = false;
		}

		if (gamepadInput.a) {
			spacebarPressed = true;
		} else {
			spacebarPressed = false;
		}
	} else {
		Input& input = this->getComponent<Input>();
		input.update();
		if (input.keyE) {
			eKeyPressed = true;
		} else {
			eKeyPressed = false;
		}

		if (input.spacebar) {
			spacebarPressed = true;
		} else {
			spacebarPressed = false;
		}
	}
}

//Checks if any keys are down
void Player::move() {
	if (local) {
		GamepadInput gamepadInput = this->getComponent<GamepadInput>();

		if (!gamepadInput.up && !gamepadInput.down) {
			plyrClass->updateVelocityY(0);

			if (!plyrClass->getIsAttacking() && !plyrClass->isRespawning()) {
				plyrClass->setIdleAnim();
			}
		}

		if (!gamepadInput.left && !gamepadInput.right) {
			plyrClass->updateVelocityX(0);

			if (!plyrClass->getIsAttacking() && !plyrClass->isRespawning()) {
				plyrClass->setIdleAnim();
			}
		}

		if (gamepadInput.up) {
			plyrClass->updateVelocityY(-1);
			if (!plyrClass->getIsAttacking()) {
				plyrClass->changeAnimation("walkUp");
			}
			
			plyrClass->setDirection(HeroType::directions::UP);
		}

		if (gamepadInput.left) {
			plyrClass->updateVelocityX(-1);
			if (!plyrClass->getIsAttacking()) {
				plyrClass->changeAnimation("walkLeft");
			}
			
			plyrClass->setDirection(HeroType::directions::LEFT);
		}

		if (gamepadInput.down) {
			plyrClass->updateVelocityY(1);
			if (!plyrClass->getIsAttacking()) {
				plyrClass->changeAnimation("walkDown");
			}
			
			plyrClass->setDirection(HeroType::directions::DOWN);
		}

		if (gamepadInput.right) {
			plyrClass->updateVelocityX(1);
			if (!plyrClass->getIsAttacking()) {
				plyrClass->changeAnimation("walkRight");
			}
			
			plyrClass->setDirection(HeroType::directions::RIGHT);
		}
	} else {
		Input input = this->getComponent<Input>();

		if (!input.keyW && !input.keyS) {
			plyrClass->updateVelocityY(0);

			if (!plyrClass->getIsAttacking()) {
				plyrClass->setIdleAnim();
			}
		}

		if (!input.keyA && !input.keyD) {
			plyrClass->updateVelocityX(0);

			if (!plyrClass->getIsAttacking()) {
				plyrClass->setIdleAnim();
			}
		}

		if (input.keyW) {
			plyrClass->updateVelocityY(-1);
			plyrClass->changeAnimation("walkUp");
			plyrClass->setDirection(HeroType::directions::UP);
		}

		if (input.keyA) {
			plyrClass->updateVelocityX(-1);
			plyrClass->changeAnimation("walkLeft");
			plyrClass->setDirection(HeroType::directions::LEFT);
		}

		if (input.keyS) {
			plyrClass->updateVelocityY(1);
			plyrClass->changeAnimation("walkDown");
			plyrClass->setDirection(HeroType::directions::DOWN);
		}

		if (input.keyD) {
			plyrClass->updateVelocityX(1);
			plyrClass->changeAnimation("walkRight");
			plyrClass->setDirection(HeroType::directions::RIGHT);
		}

		if (input.keyC) {
			// prints player's coordinates
			std::cout << "X: " << plyrClass->getComponent<TransformComponent>().position.x << std::endl;
			std::cout << "Y: " << plyrClass->getComponent<TransformComponent>().position.y << std::endl;
		}
	}
}

void Player::actions() {

}

void Player::setManager(Manager *manager) {
	//this->manager = manager;
	//std::cout << "player manager set to: " << manager << std::endl;
}

//Shoot the weapon in the direction of the mouse cursor
void Player::attack() {

	if (spacebarPressed && !plyrClass->getHasStartedMining()) {
		plyrClass->attack();
		plyrClass->playAttackAnimation();
	}

}

int Player::getHealth() {
	return plyrClass->getComponent<HealthComponent>().getHealth();
}

void Player::damagePlayer(int dmg) {
	plyrClass->takeDamage(dmg);
	//std::cout << lastDamage - 500 << std::endl;
	/*if (SDL_GetTicks() > (lastDamage + 500)) {

		this->getComponent<HealthComponent>().damageHealth(1);
		std::cout << "Health: " << this->getComponent<HealthComponent>().getHealth() << std::endl;
		lastDamage = SDL_GetTicks();
		uiManager->healthUI->updateHealth(this->getComponent<HealthComponent>().getHealth());  // update healthUI
	}

	if (this->getComponent<HealthComponent>().getHealth() <= 0) {

		//killPlayer();

	}*/

}

// For Debugging purposes
void Player::tryToMine() {
	if (Physics::collidesWithMine(this->getComponent<ColliderComponent>().collider)) {
		std::cout << "Colliding with mine" << std::endl;   // For Debugging purposes
	}
}
