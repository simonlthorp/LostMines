#include "JoinScene.h"
#include "../../Engine/Game.h"
#include "../UI/TextUI.h"
#include "../UI/TextInputUI.h"
#include "../UI/DynamicUI.h"
#include "../../Engine/Texture/TextureManager.h"

#include <iterator>
#include <vector>

JoinScene::JoinScene() {}
JoinScene::~JoinScene() {}


void JoinScene::init() {
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

	//Text
	TextUI::setTextSize("Arialbd_20", "Address:", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 150;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("addressText", UILabels::text, "Arialbd_20", dest, color, "Address:");
	uiComponents.push_back(button);

	//Address
	TextInputUI::setTextSize("Arialbd_20", "255.255.255.255", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextInputUI("address", UILabels::inputText, "Arialbd_20", dest, color, "255.255.255.255");
	button->setActionForInput([](std::vector<UI*> ui) {
		TextInputUI* textInputUI = (TextInputUI*) ui.at(0);
		if (Game::event.type == SDL_KEYDOWN) {
			//std::cout << "Keydown" << std::endl;
			const char* input = SDL_GetKeyName(Game::event.key.keysym.sym);
			if (isdigit(input[0]) || Game::event.key.keysym.sym == SDLK_PERIOD) {
				//std::cout << "Event: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
				std::string value = textInputUI->getText();
				if (value.size() < 15) {
					value += std::string(SDL_GetKeyName(Game::event.key.keysym.sym));
					textInputUI->changeText(value);
				}
			}
			if (Game::event.key.keysym.sym == SDLK_BACKSPACE && !textInputUI->keyDown) {
				textInputUI->keyDown = true;
				//std::cout << "backspace" << std::endl;
				std::string value = textInputUI->getText();
				if (value.size() > 0) {
					value.pop_back();
				}
				textInputUI->changeText(value);
			}
		} else {
			textInputUI->keyDown = false;
		}
		//}
	});
	uiComponents.push_back(button);

	//Text
	TextUI::setTextSize("Arialbd_20", "Name:", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 150;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 20;
	button = new TextUI("addressText", UILabels::text, "Arialbd_20", dest, color, "Name:");
	uiComponents.push_back(button);

	//Name
	TextInputUI::setTextSize("Arialbd_20", "Player1", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 20;
	button = new TextInputUI("name", UILabels::inputText, "Arialbd_20", dest, color, "Player1");
	button->setActionForInput([](std::vector<UI*> ui) {
		TextInputUI* textInputUI = (TextInputUI*) ui.at(0);
		if (Game::event.type == SDL_KEYDOWN) {
			//std::cout << "Keydown" << std::endl;
			const char* input = SDL_GetKeyName(Game::event.key.keysym.sym);
			if (isdigit(input[0]) || (isalpha(input[0]) && Game::event.key.keysym.sym != SDLK_BACKSPACE)) {
				//std::cout << "Event: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
				std::string value = textInputUI->getText();
				if (value.size() < 15) {
					tolower('c');

					value += std::string(SDL_GetKeyName(Game::event.key.keysym.sym));
					textInputUI->changeText(value);
				}
			}
			if (Game::event.key.keysym.sym == SDLK_BACKSPACE && !textInputUI->keyDown) {
				textInputUI->keyDown = true;
				//std::cout << "backspace" << std::endl;
				std::string value = textInputUI->getText();
				if (value.size() > 0) {
					value.pop_back();
				}
				textInputUI->changeText(value);
			}
		}
		else {
			textInputUI->keyDown = false;
		}
		//}
	});
	uiComponents.push_back(button);

	//join
	TextUI::setTextSize("Arialbd_20", "Join", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 80;
	button = new TextUI("join", UILabels::linkedText, "Arialbd_20", dest, color, "Join");
	button->addLinkedItem("address");
	button->addLinkedItem("name");
	//Check whether the address is proper!
	button->setActionForInput([](std::vector<UI*> ui) {
		//ui = the variable you are evaluating or checking
		TextInputUI* evaluatedUI;
		std::vector<std::string> data;

		evaluatedUI = (TextInputUI*)ui.at(0);
		data.push_back(evaluatedUI->getText());
		std::cout << "Address: " << evaluatedUI->getText() << std::endl;

		evaluatedUI = (TextInputUI*)ui.at(1);
		data.push_back(evaluatedUI->getText());
		std::cout << "Name: " << evaluatedUI->getText() << std::endl;

		SceneManager::changeScenes("lobbyScene", data);

		//std::cout << "Address: " << value << std::endl;
	});
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

void JoinScene::handleEvents() {
	updateMouse();
	//if (SDL_IsTextInputActive()) {
		updateKeyboardInput();
	//}
}

void JoinScene::update() {
	//SDL_StartTextInput();
	//std::cout << keystates << std::endl;

	//SDL_StopTextInput();
}

void JoinScene::render() {
	for (int i = 0; i < uiComponents.size(); i++) {
		uiComponents.at(i)->render();
	}
	//Labels -----------

	//------------------
}

void JoinScene::loadScene() {
	//Nothing
}

//Mouse
void JoinScene::updateMouse() {
	//Shoot at mouse cursor
	if (Game::event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT) && mouseDown == false) {
		mouseDown = true;
		if (SDL_GetMouseState(&mouse_x, &mouse_y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
			
			if (currentInputEnabled != nullptr && !currentInputEnabled->withinUI(getMouseX(), getMouseY())) {
				currentInputEnabled->disableTextInput();
				currentInputEnabled = nullptr;
			}

			//left click
			//std::cout << getMouseX() << " " << getMouseY() << std::endl;
			for (int i = 0; i < uiComponents.size(); i++) {
				if (uiComponents.at(i)->withinUI(getMouseX(), getMouseY())) {
					if (uiComponents.at(i)->getType() == UILabels::inputText) {
						TextInputUI* text = (TextInputUI*)uiComponents.at(i);
						text->enableTextInput();
						currentInputEnabled = text;
						//std::cout << "ID: " << text->getID() << std::endl;
					}
					else if (uiComponents.at(i)->getType() == UILabels::linkedImage || uiComponents.at(i)->getType() == UILabels::linkedText) {
						std::vector<UI*> values = UI::getVectorUI(uiComponents, uiComponents.at(i)->getLinkedItems());
						uiComponents.at(i)->callActionFunctionUI(values);
					}
					else if (uiComponents.at(i)->getType() == UILabels::dynamicUI) {
						uiComponents.at(i)->callActionFunctionUI();
					}
					else {
						uiComponents.at(i)->callActionFunction();
					}
					//std::cout << uiComponents.at(i)->getID() << std::endl;
				}
			}
		}
	}
	else if (Game::event.type == SDL_MOUSEBUTTONUP && SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseDown = false;
	}
}

void JoinScene::updateKeyboardInput() {
	if (currentInputEnabled == nullptr) {
		//std::cout << "nullptr" << std::endl;
		return;
	}
	currentInputEnabled->callActionFunctionUI();
}

int JoinScene::getMouseX() {
	return mouse_x;
}

int JoinScene::getMouseY() {
	return mouse_y;
}