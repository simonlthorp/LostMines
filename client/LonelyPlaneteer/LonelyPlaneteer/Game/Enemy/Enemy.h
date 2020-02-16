#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../Map/MapManager.h"
#include "../AddOns/Sword.h"
#include "../Map/MobArea.h"
//#include "MapManager.h"

/*------------------------------------------------------------------------------------------------
-- SOURCE FILE: Enemy.h
--
-- FUNCTIONS:   Enemy(float, float, Player *)
--              void update() override
--              void draw(SDL_Rect cam) override
--              void updatePosition()
--              void setPosition(float, float)
--              void move()
--              void chase(const Player *)
--              void patrol()
--              void wander()
--              void face()
--
--
-- DATE:        October 15, 2017
--
-- DESIGNER:    Maitiu Morton, Simon Thorp & Michael Goll
--
-- PROGRAMMER:  Maitiu Morton & Michael Goll
--
-- NOTES:       Class for the "Enemy" character type in the game.
--              Handles all operations of the enemies in the game.
--------------------------------------------------------------------------------------------------*/

#include "../../Engine/ECS/Component.h"
#include "../Objects/Player.h"
#include "EnemyState.h"

#define CHASE_DISTANCE 200
#define GIVE_UP_DISTANCE 300
#define WANDER_RADIUS 100
#define DEATH_LOCATION -300

class Player;

class Enemy : public Entity {
private:
	std::vector<Player*> players;
	std::vector<MobArea*> mobAreas;
	EnemyState state;
	MapManager *mm;
	RespawnPoint rp;
	MobArea* mobArea;
	float goalX, goalY;
	Uint32 playerCollideTime;
	bool collidingWithPlayer = false;
	Uint32 diedAtTime = 0;
	bool isDead = false;
	Uint32 respawnTime = 2000;
	Uint32 timeOfDeath;
	//Animation Variables
	Animator* animator;
	int facingDirection; // The direction the enemy is facing
	int attackLength; // The time in miliseconds of the attack animation
	int attackTime; //The time that an attack is initiated
	bool isAttacking = false;
	//int animIndex = 0;
	//int frames = 0;
	//int animSpeed = 0;
	
	//std::map<const char*, Animation> animations;
	float attackRange = 20.000f;
	//Pathfinding variables
	//std::vector<PathNode*> path;
	//SDL_Point followPoint;
	SDL_Point path;

	Uint32 lastAttack = 0;
	Uint32 attackDelay = 2000;
	int chaseDist = 20;
	int attackDist = 30;
	int damage = 20;

	Sword* sword;


	enum directions
	{
		UP, DOWN, LEFT, RIGHT
	};

public:
	Enemy(std::vector<Player*> p, std::vector<MobArea*> m);

	~Enemy();

	void update() override;

	void draw() override;

	void updatePosition();

	void updateAnimation();

	void setPosition(float x, float y);

	void setPath(int x, int y);

	bool getIsDead();

	void move();

	void chase(Player *);

	void wander();

	void face();

	void checkCollision();

	void hitPlayer();

	void killEnemy();

	//Animation
	void play(const char* animName);

	void attack(Player* p);

	void takeDamage(int dmg);

	void respawn();

	void updateSwordPosition();
};