#pragma once

#include "Animation.h"
#include <map>

class Animator
{
public:
	Animator();
	void playAnimation(const char* animName);
	void addAnimation(const char* animName, Animation animation);
	Animation getAnimation(const char* animName);
	const char* getCurrent();

private:
	std::map<const char*, Animation> animations;
	const char* currentAnimation;

};
