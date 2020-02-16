#pragma once
#include "Mine.h"
#include "../Scene/GameScene.h"
#include "../../Engine/Physics/Collision.h"
//  Mine.cpp  by Zac Koop.  February 2019

// Mine constructor (Xpos, Ypos, ID, CLASS, ACTIVE)
Mine::Mine(float x, float y, const int ID, const unsigned int type, bool active) : Entity(GameScene::manager) {
	setMineID(ID);
	setMineType(type);
	setActive(active);
	posX = x;
	posY = y;
	this->addComponent<TransformComponent>(x, y, 192, 192, 1);
	this->addComponent<SpriteComponent>("ControlPoints");
	this->getComponent<SpriteComponent>().setSrc(0, 0);
	this->addComponent<ColliderComponent>("Mine");
	this->getComponent<ColliderComponent>().setColliderSize(80, 80);
	this->getComponent<ColliderComponent>().setCollider(x, y);
	this->addGroup(mineGroup);
	this->setLayer(topLayer);
	int sc = this->getComponent<TransformComponent>().scale;
	this->getComponent<SpriteComponent>().setDest(x, y, sc);

	animator = new Animator();
	animator->addAnimation("knight", Animation(0, 1, 100));
	animator->addAnimation("wizard", Animation(1, 1, 100));
	animator->addAnimation("inactive", Animation(2, 1, 100));
	animator->addAnimation("knightGems", Animation(3, 7, 100));
	animator->addAnimation("wizardGems", Animation(4, 7, 100));

	setMineSprite(type, active);

	currentPoints = static_cast<float>(MINE_POINT_TOTAL);
	pointRatio = static_cast<float>(MINE_POINT_TOTAL) / static_cast<float>(MINE_SPEED_CONSTANT);

	current_time = 0;
}


void Mine::update() {
	int ticks = SDL_GetTicks();
	delta_time = static_cast<float>(ticks - current_time);
	current_time = ticks;

	TransformComponent *tc = &this->getComponent<TransformComponent>();
	this->getComponent<ColliderComponent>().updateCollider();

	if (animating) {
		miningAnimation();
	} else {
		setMineSprite(mineType, active);
	}

	updateAnimation();
}


void Mine::draw() {
	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
	SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();//get destination rect
	SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();//get source rect 
	SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture(); // get the texture
	TextureManager::Draw(tex, src, dest, 0);

	//mineZone->draw();
}

// Returns whether the mine is Active or Not
bool Mine::canPlayerMine(unsigned int playerType) {
	//std::cout << "Inside playerCanMine" << std::endl;

	if (!active) {
		std::cout << "Mine is not currently active" << std::endl;
		return false;
	}

	if (playerType == mineType) {
		//mineResources();
		return true;
	} else {
		std::cout << "Player is the wrong type to mine here" << std::endl;
		return false;
	}
}


// Mining Mechanic
float Mine::mineResources(HeroType& player) {
	if (currentPlayer == nullptr) {
		currentPlayer = &player;
	}

	animating = true;
	float result = 0.0f;

	if (currentPoints > 0 && !finishedMining) {
		result = pointRatio * delta_time;

		currentPoints -= result;
		currentlyMining = true;
		Game::mixer->mineGems1->play();

		//mine
		//std::cout << "Mining Resources" << std::endl;
		//std::cout << "timeToMine: " << timeToMine << std::endl;
	} else {
		//std::cout << "Finished Mining" << std::endl;
		finishedMining = true;
		currentlyMining = false;
		active = false;
		resetMine();
		currentPlayer = nullptr;
		animating = false;
		return 0.0f;
	}

	return result;  // points for player
}


void Mine::setMineSprite(const unsigned int type, const bool active) {
	if (!active)
		animator->playAnimation("inactive");
	else if (type == 0)
		animator->playAnimation("knight");
	else if (type == 1)
		animator->playAnimation("wizard");
}


void Mine::miningAnimation() {
	if (mineType == 0)
		animator->playAnimation("knightGems");
	else if (mineType == 1)
		animator->playAnimation("wizardGems");
}



void Mine::updateAnimation() {

	this->getComponent<SpriteComponent>().setSrc(
		this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>((SDL_GetTicks() / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
		animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
}

void Mine::stopAnimating(HeroType& player) {
	if (currentPlayer != nullptr)
	{
		if (currentPlayer == &player) {
			currentPlayer = nullptr;
			animating = false;
		}
	}
}



void Mine::resetMine() {
	currentPoints = MINE_POINT_TOTAL;
	finishedMining = false;
	currentlyMining = false;
}


void Mine::collisionResponse(Collision* collision) {

	if (collision->type == CollisionType::movement_mine) {
		std::cout << "HERE!!! Movment mine" << std::endl;
	}

	if (collision->type == CollisionType::mine_player) {
		std::cout << "HERE!!!" << std::endl;
	}

	if (collision->type != CollisionType::mine_player) {
		currentlyMining = false;
	}
}


