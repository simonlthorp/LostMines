#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/ECS/Component.h"
#include "../Animation/Animator.h"
#include <map>

#define MINE_POINT_TOTAL 250
#define MINE_SPEED_CONSTANT 5000

class HeroType;

class Mine: public Entity {
private: 
	float posX, posY;
	int ID;
	unsigned int mineType;
	bool active = false;
	bool finishedMining = false;
	bool currentlyMining = false;
	float pointRatio = 0.0f;
	float currentPoints = 0.0f;
	bool animating = false;
	HeroType* currentPlayer = nullptr;

	float delta_time = 0.0f;
	int current_time = 0;

protected:
	Animator* animator;

public:
	// Mine constructor (Xpos, Ypos, ID, CLASS, ACTIVE, AmntResources)
	Mine(float x, float y, const int ID, const unsigned int type, bool active);

	void setMineID(const int id) {
		ID = id;
	}

	int getMineID() {
		return ID;
	}

	int getXPos() {
		return static_cast<int>(posX);
	}

	int getYPos() {
		return static_cast<int>(posY);
	}

	// Set the mine to the player class (knight or wizard 0 or 1)
	void setMineType(const unsigned int type) {
		mineType = type;
	}

	// Activate mine
	void setActive(bool canMine) {
		active = canMine;
	}

	bool getActive() {
		return active;
	}

	void setKeyPressTime(Uint32 time);

	void setCurrentlyMining(bool curMining) {
		currentlyMining = curMining;
	}


	void resetMine();

	void update() override;
	void draw() override;
	void collisionResponse(Collision* collision) override;

	bool canPlayerMine(unsigned int playerType);
	float mineResources(HeroType& player);
	void setMineSprite(const unsigned int type, const bool active);
	void miningAnimation();
	void updateAnimation();

	void stopAnimating(HeroType& player);
};
