#pragma once
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/ECS/Component.h"
#include "../../Engine/Physics/Physics.h"
#include "../Classes/HeroType.h"
#include "../Classes/Knight.h"
#include "../Classes/Wizard.h"
#include <memory>
#include <map>


class Player : public Entity {
private:
	int animIndex = 0;
	//std::map<const char*, Animation> animations;
	int frames = 0;
	int speed = 100;
	Manager* manager;
	Uint32 lastShot;
	Uint32 lastDamage = 0;
	bool isDead = false;
	unsigned int lastETime = 0;
	int state = 0;
	std::unique_ptr<HeroType> plyrClass;
	int classType = 0;
	bool eKeyPressed = false;
	//bool xButtonPressed = false;
	bool spacebarPressed = false;
	Uint32 keyTime = 0;
	bool local = false;

public:
	Player(HeroType *c, bool isLocal);

	void eventHandle();

	void update() override;

	void draw() override;

	void updatePosition();

	void updateAnimation();

	void move();

	void animate();

	void getInput();

	void play(const char* animName);

	void attack();

	void setManager(Manager *manager);

	void setStateTo(const int s);

	void actions();

	int getHealth();

	void damagePlayer(int dmg);

	HeroType* getClass() { return plyrClass.get(); }

	void tryToMine();

	TransformComponent& getTransformComponent();

	//void killPlayer();

	inline bool getEKeyPressed() { return eKeyPressed; }
	//inline bool getXButtonPressed() { return xButtonPressed; }
	inline bool getSpacebarPressed() { return spacebarPressed; }
	inline HeroType* getPlyrClass() { return plyrClass.get(); }
};