
#pragma once
#include "../../Engine/ECS/ECS.h"

class HealthComponent : public Component {
private:
	int health;
	int maxHealth;

public:
	SDL_Rect border;
	SDL_Rect healthBar;

	HealthComponent(int h) { 
		health = h;
		maxHealth = h;
		border.w = 60;
		border.h = 10;
		healthBar.w = 50;
		healthBar.h = 5;
	};

	~HealthComponent() {};

	int getHealth() { return health; };

	void resetHealth() {
		health = maxHealth;
		healthBar.w = health / 2;
	}

	void damageHealth(int d) { 
		
		health -= d; 
		if (health >= 0) {
			healthBar.w = health / 2;
		}

	};

	void setPosition(int x, int y, int w, int h) {
		border.x = x + w / 2 - border.w / 2;
		border.y = y + h  / 2 - border.h / 2 - 32;

		healthBar.x = border.x + (border.w - healthBar.w) / 2 - (maxHealth / 4 - health / 4);
		healthBar.y = border.y + (border.h - healthBar.h) / 2;
	}
};