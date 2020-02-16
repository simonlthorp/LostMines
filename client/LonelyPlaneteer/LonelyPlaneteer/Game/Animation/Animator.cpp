
#include "Animator.h"

Animator::Animator() {}

void Animator::addAnimation(const char* animName, Animation animation) {
	animations.emplace(animName, animation);
}

void Animator::playAnimation(const char* animName) {
	currentAnimation = animName;
}

Animation Animator::getAnimation(const char* animName) {

	return animations.at(animName);

}

const char* Animator::getCurrent() {

	return currentAnimation;

}
