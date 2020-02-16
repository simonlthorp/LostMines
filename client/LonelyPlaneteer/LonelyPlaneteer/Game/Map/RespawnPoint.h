#pragma once
#ifndef RESPAWN_POINT_H
#define RESPAWN_POINT_H

class RespawnPoint {
public:
	RespawnPoint() { 
		xPos = 0; 
		yPos = 0;
	};

	RespawnPoint(int x, int y) {
		xPos = x;
		yPos = y;
	};

	int getX() { return xPos; };
	int getY() { return yPos; };

private:
	int xPos;
	int yPos;
	//int score = 0;
};

#endif