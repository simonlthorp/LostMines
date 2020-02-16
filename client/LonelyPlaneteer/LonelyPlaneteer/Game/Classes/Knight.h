#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

#include "HeroType.h"
#include "../AddOns/Sword.h"
 
class Knight : public HeroType {
public:
	Knight() {};

	Knight(int t);
	void playAttackAnimation() override;
	Sword* getSword() override;
private:
	const char* spriteStr = "Knight";
};

#endif // !KIGHT_H
