#pragma once
#include "../../Engine/ECS/ECS.h"

class CombatComponent : public Component {
private:
	int damage;

public:
	CombatComponent(int d) { damage = d; };

	int getDamage() { return damage; };
}; 
