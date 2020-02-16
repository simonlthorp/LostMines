#pragma once
#ifndef WIZARD_H
#define WIZARD_H

#include "HeroType.h"

class Wizard : public HeroType {
public:
	Wizard() {};

	Wizard(int t);
	void playAttackAnimation() override;
private:
	int damage = 10;
	int health = 15;
	const char* spriteStr = "Mage";
};

#endif // !WIZARD_H
