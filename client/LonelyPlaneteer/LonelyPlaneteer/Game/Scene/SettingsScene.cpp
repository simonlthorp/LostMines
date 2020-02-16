#include "SettingsScene.h"
#include "../../Engine/Game.h"
#include "../UI/TextUI.h"
#include "../../Engine/Texture/TextureManager.h"

SettingsScene::SettingsScene() {}
SettingsScene::~SettingsScene() {}


void SettingsScene::init() {
	UI* button;

	SDL_Rect dest, src;
	SDL_Color color = { 255,255,255,255 };

	//Background
	dest.w = 1920;
	dest.h = 1080;
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	src.w = 1440;
	src.h = 900;
	src.x = 0;
	src.y = 0;
	button = new UI("background", UILabels::image, "wallpaper1", src, dest);
	uiComponents.push_back(button);

	//Back
	TextUI::setTextSize("Arialbd_20", "Lost Mines", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = 0 + (20);
	dest.y = (Game::camera.h) - (dest.h + 10);
	button = new TextUI("back", UILabels::text, "Arialbd_20", dest, color, "Back");
	button->setAction([]() {
		SceneManager::changeScenes("menuScene");
	});
	uiComponents.push_back(button);
}

void SettingsScene::handleEvents() {
	updateMouse();
}
void SettingsScene::update() {}

void SettingsScene::render() {
	for (int i = 0; i < uiComponents.size(); i++) {
		uiComponents.at(i)->render();
	}
	//Labels -----------

	//------------------
}

void SettingsScene::loadScene() {
	//Nothing
}

//Mouse
void SettingsScene::updateMouse() {
	//Shoot at mouse cursor
	if (Game::event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT) && mouseDown == false) {
		if (SDL_GetMouseState(&mouse_x, &mouse_y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
			//left click
			//std::cout << getMouseX() << " " << getMouseY() << std::endl;
			for (int i = 0; i < uiComponents.size(); i++) {
				if (uiComponents.at(i)->withinUI(getMouseX(), getMouseY())) {
					uiComponents.at(i)->callActionFunction();
					//std::cout << uiComponents.at(i)->getID() << std::endl;
				}
			}
		}
	}
	else if (Game::event.type == SDL_MOUSEBUTTONUP && SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseDown = false;
	}
}

int SettingsScene::getMouseX() {
	return mouse_x;
}

int SettingsScene::getMouseY() {
	return mouse_y;
}