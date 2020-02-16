#include "LoadingScene.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"

LoadingScene::LoadingScene() {}
LoadingScene::~LoadingScene() {}

void LoadingScene::init() {
	circle1 = Game::assetManager.getTexture("circle1");
	circle2 = Game::assetManager.getTexture("circle2");
	circle3 = Game::assetManager.getTexture("circle3");
	circle4 = Game::assetManager.getTexture("circle4");
	circle5 = Game::assetManager.getTexture("circle5");
	circle6 = Game::assetManager.getTexture("circle6");
	circle7 = Game::assetManager.getTexture("circle7");
	circle8 = Game::assetManager.getTexture("circle8");
	circle9 = Game::assetManager.getTexture("circle9");
	circle10 = Game::assetManager.getTexture("circle10");
	circle11 = Game::assetManager.getTexture("circle11");

	destCircle.w = Game::camera.w / 2;
	destCircle.h = Game::camera.w / 2;
	destCircle.x = (Game::camera.w / 2) - (destCircle.w / 2);
	destCircle.y = (Game::camera.h / 2) - (destCircle.h / 2);

	srcCircle.w = 894;
	srcCircle.h = 894;
	srcCircle.x = 0;
	srcCircle.y = 0;

	background = Game::assetManager.getTexture("loadBackground");
	destBackground.w = Game::camera.w;
	destBackground.h = Game::camera.h;
	destBackground.x = (Game::camera.w / 2) - (destBackground.w / 2);
	destBackground.y = (Game::camera.h / 2) - (destBackground.h / 2);

	srcBackground.w = 663;
	srcBackground.h = 492;
	srcBackground.x = 0;
	srcBackground.y = 0;
}

void LoadingScene::handleEvents() {}

void LoadingScene::update() {
	incrementCounter();
}

void LoadingScene::render() {
	TextureManager::Draw(background, srcBackground, destBackground, 0);
	TextureManager::Draw(circle1, srcCircle, destCircle, circle1Counter);
	TextureManager::Draw(circle2, srcCircle, destCircle, circle2Counter);
	TextureManager::Draw(circle3, srcCircle, destCircle, circle3Counter);
	TextureManager::Draw(circle4, srcCircle, destCircle, circle4Counter);
	TextureManager::Draw(circle5, srcCircle, destCircle, circle5Counter);
	TextureManager::Draw(circle6, srcCircle, destCircle, circle6Counter);
	TextureManager::Draw(circle7, srcCircle, destCircle, circle1Counter);
	TextureManager::Draw(circle8, srcCircle, destCircle, circle2Counter);
	TextureManager::Draw(circle9, srcCircle, destCircle, circle3Counter);
	TextureManager::Draw(circle10, srcCircle, destCircle, circle4Counter);
	TextureManager::Draw(circle11, srcCircle, destCircle, circle5Counter);
}

void LoadingScene::loadScene() {

}

void LoadingScene::incrementCounter() {
	circle1Counter += 1;
	if (circle1Counter > 360) {
		circle1Counter = 0;
	}

	circle2Counter += 2;
	if (circle2Counter > 360) {
		circle2Counter = 0;
	}

	circle3Counter += 3;
	if (circle3Counter > 360) {
		circle3Counter = 0;
	}

	circle4Counter += 4;
	if (circle4Counter > 360) {
		circle4Counter = 0;
	}

	circle5Counter += 5;
	if (circle5Counter > 360) {
		circle5Counter = 0;
	}

	circle6Counter += 6;
	if (circle6Counter > 360) {
		circle6Counter = 0;
	}
}