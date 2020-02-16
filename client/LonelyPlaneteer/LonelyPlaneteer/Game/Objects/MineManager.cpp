#pragma once
#include "MineManager.h"
// MineManager.cpp  By Zac Koop.  February 2019

MineManager::MineManager(std::vector<Mine*> mines) : Entity(GameScene::manager) {
	this->minesList = mines;

	for (auto& mine : mines) {
		if (mine->getActive()) {
			this->curActiveMine = mine->getMineID();
		}
	}
	//resetActiveMine();
}


void MineManager::update() {
	for (Mine* mine : minesList) {
		if (mine->getActive()) {
			return;
		}
	}

	// else if there is NO active mines....reset a new active mine
	resetActiveMine();
}


void MineManager::draw() {
}


// Get the mine that is currently active
Mine* MineManager::getActiveMine() {
	for (auto& mine : minesList) {
		if (mine->getActive()) {
			return mine;
		}
	}

	return nullptr;
}


// Returns the address of a mine corresponding to the MineID that is passed in as a parameter.
Mine* MineManager::getMineByID(const int id) {
	for (auto& mine : minesList) {
		if (mine->getMineID() == id) {
			return mine;
		}
	}

	std::cout << "RAND Mine ID: " << id << std::endl;
	std::cout << "MinesList Size: " << minesList.size() << std::endl;

	return nullptr;
}


// deactivates the active mine and picks a new mine to activate.
void MineManager::resetActiveMine() {
	std::cout << "calling RESET active mine" << std::endl;
	std::vector<Mine*> activeCandidates;

	// create a list of the mines that are NOT currently active. 
	for (auto& mine : minesList) {
		if (mine->getMineID() != curActiveMine) {
			activeCandidates.push_back(mine);
		}
	}

	// Deactivate the current active mine.
	deactivateMine(curActiveMine);

	int randMineIndex = rand() % ((activeCandidates.size() - 1) - 0 + 1) + 0;   // Index 0 is Min.  list.size()-1 is Max.
	int randType = rand() % ((1) - 0 + 1) + 0;   // Index 0 is Min.  1 is Max.
	Mine* nextMine = activeCandidates[randMineIndex];
	nextMine->setMineType(randType);
	//nextMine->setMineType(0);   // For testing in Single Player mode only.
	nextMine->setActive(true);
	nextMine->resetMine();
	curActiveMine = nextMine->getMineID();
}


// Deactivates a mine corresponding to the MineID that is passed in as a parameter.
void MineManager::deactivateMine(const int id) {
	Mine* mine = getMineByID(id);

	if (mine != nullptr && mine->getActive()) {
		mine->setActive(false);
		mine->resetMine();
	}
}

