#include "MenuScene.h"
#include "../../Engine/Game.h"
#include "../UI/TextUI.h"
#include "../../Engine/Texture/TextureManager.h"

AudioMixer* Game::mixer;

MenuScene::MenuScene() {}
MenuScene::~MenuScene() {}


void MenuScene::init() {
	UI* button;

	SDL_Rect dest, src;
	SDL_Color color = {255,255,255,255};

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

	//Title
	TextUI::setTextSize("Arialbd_64", "Lost Mines", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2) - 100;
	titleText = new TextUI("title", UILabels::text, "Arialbd_64", dest, color, "Lost Mines");

	//Join
	TextUI::setTextSize("Arialbd_20", "Start Game", &dest.w, &dest.h);
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("join", UILabels::text, "Arialbd_20", dest, color, "Start Game");
	button->setAction([]() {
		SceneManager::changeScenes("lobbyScene");
		//SceneManager::changeScenes("gameScene", true);
	});
	uiComponents.push_back(button);

	//Settings
	TextUI::setTextSize("Arialbd_20", "Settings", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("settings", UILabels::text, "Arialbd_20", dest, color, "Settings");
	button->setAction([]() {
		SceneManager::changeScenes("settingsScene");
	});
	uiComponents.push_back(button);

	//Quit
	TextUI::setTextSize("Arialbd_20", "Quit", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w) - (dest.w + 20);
	dest.y = 0 + (20);

	/*dest.x = 0 + (20);
	dest.y = (Game::camera.h) - (dest.h + 10);*/
	button = new TextUI("quit", UILabels::text, "Arialbd_20", dest, color, "Quit");
	button->setAction([]() {
		//May need to change this
		std::cout << "Quitting" << std::endl;
		SDL_Quit();
	});
	uiComponents.push_back(button);

	//Play menu music
	Game::mixer->playMusic(AudioMixer::menu_music);
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME/2);

	////How to setup a image
	//dest.w = 200;
	//dest.h = 50;
	//dest.x = ((Game::camera.w / 2) - (200 / 2));
	//dest.y = ((Game::camera.h / 2) - (50 / 2));
	//src.w = 691;
	//src.h = 150;
	//src.x = 0;
	//src.y = 0;
	//button = new UI("button", UILabels::image, "Button", src, dest);
	//uiComponents.push_back(button);
}

void MenuScene::handleEvents() {
	updateMouse();
}

void MenuScene::update() {}

void MenuScene::render() {
	for (int i = 0; i < uiComponents.size(); i++) {
		uiComponents.at(i)->render();
	}
	//Labels -----------
	titleText->render();
	//------------------



	//TextureManager::Draw(background, srcBackground, destBackground, Game::camera, 0);

	//TextureManager::Draw(title, srcTitle, destTitle, Game::camera, 0);
	////printf("Render Loading\n");
}

void MenuScene::loadScene() {
	//Nothing
}

//Mouse
void MenuScene::updateMouse() {
	//Shoot at mouse cursor
	if (Game::event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT) && mouseDown == false) {
		mouseDown = true;
		if (SDL_GetMouseState(&mouse_x, &mouse_y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
			//left click
			//std::cout << getMouseX() << " " << getMouseY() << std::endl;
			for (int i = 0; i < uiComponents.size(); i++) {
				if (uiComponents.at(i)->withinUI(getMouseX(), getMouseY())) {
					uiComponents.at(i)->callActionFunction();
					//std::cout << uiComponents.at(i).getID() << std::endl;
				}
			}
		}
	}
	else if (Game::event.type == SDL_MOUSEBUTTONUP && SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseDown = false;
	}
}

int MenuScene::getMouseX() {
	return mouse_x;
}

int MenuScene::getMouseY() {
	return mouse_y;
}