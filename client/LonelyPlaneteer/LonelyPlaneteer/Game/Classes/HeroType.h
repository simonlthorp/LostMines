#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"
#include "../../Engine/Physics/Physics.h"
#include "../Animation/Animator.h"
#include "../AddOns/Sword.h"
#include "../Map/RespawnPoint.h"
#include "../AddOns/MovementBounds.h"
#include "../AddOns/Projectile.h"
//#include "../Objects/Mine.h"
//#include "../Objects/Player.h"
#include <stack> 

class Player;

class HeroType : public Entity {
protected:

	Player* player;
	Animator* animator;
	Sword* sword;
	Mine* currentMine = nullptr;
	RespawnPoint respawnPoint;
	MovementBounds* movementB;

	unsigned int type;
	std::stack<Mine*> mineStack;

	int facingDirection; // The direction the hero is facing
	int attackLength; // The time in miliseconds of the attack animation
	int attackTime; //The time that an attack is initiated
	float heroScore = 0;
	int team = 0;

	bool isAttacking = false;
	bool hasStartedMining = false;
	bool isCollidingWithMine = false;
	bool isPlayer = false;
	bool respawning = false;

	Uint32 respawnTime = 3000;
	Uint32 timeOfDeath = 0;

	Uint32 fireRate = 600;
	Uint32 lastShot = 0;

public:
	HeroType();
	virtual void attack();
	virtual void update() override;
	virtual void draw() override;
	virtual void lateUpdate() override;
	virtual void playAttackAnimation() {};
	void updateHero();
	void updatePosition();
	void collisionResponse(Collision* collision) override;
	bool seeIfPlayerCanMine();   // check if the player is of the right character class to mine
	void startMining();          // mine
	void updateVelocityY(float y);
	void updateVelocityX(float X);
	void updateAnimation();
	void changeAnimation(const char* animName);
	void setDirection(int direction);
	int getDirection();
	unsigned int getType();
	void setIdleAnim();
	void attackAnim();
	inline void addToScore(float score) { heroScore += score; } // Add up the score
	void resetScore();
	bool isRespawning();
	void respawn();
	void updateSwordPosition();
	void setToPlayer() { isPlayer = true; };

	inline int getPlayerScore() { return static_cast<int>(heroScore); };
	bool getIsAttacking();
	virtual Sword* getSword();
	inline bool getHasStartedMining() { return hasStartedMining; };
	inline void setPlayer(Player* p) { player = p; };
	void takeDamage(int dmg);
	void die();

	int getAttackDamage();
	int getTeam() { return team; };
	void shootProjectile();
	enum directions
	{
		UP, DOWN, LEFT, RIGHT
	};

	inline Player* getPlayer() { return player; }
	inline bool getIsPlayer() { return isPlayer; }
};
#endif // !CLASS_H