#pragma once
#include "Mine.h"
#include <vector>


class MineManager: public Entity {
private: 
	int curActiveMine;
	std::vector<Mine*> minesList;

public:
	MineManager(std::vector<Mine*> mines);

	void update() override;
	void draw() override;

	Mine* getActiveMine();
	Mine* getMineByID(const int id);
	void resetActiveMine();
	void deactivateMine(const int id);

};
