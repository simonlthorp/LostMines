#pragma once

struct Animation
{

	int index;
	int numberOfFrames;
	int msPerFrame;

	Animation() {}
	Animation(int i, int f, int s) {

		index = i;
		numberOfFrames = f;
		msPerFrame = s;

	}

};