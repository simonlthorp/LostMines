#include "LobbyScene.h"
#include "../../Engine/Game.h"
#include "../UI/TextUI.h"
#include "../UI/DynamicUI.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Game/Scene/GameScene.h"

LobbyScene::LobbyScene() {}
LobbyScene::~LobbyScene() {}

bool LobbyScene::ready[4] = { false };

void LobbyScene::init() {
	UI* button;

	SDL_Rect dest, src;
	SDL_Color color = { 255,255,255,255 };

	//Background
	dest.w = 1920;
	dest.h = 1080;
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	src.w = 1920;
	src.h = 1080;
	src.x = 0;
	src.y = 0;
	button = new UI("background", UILabels::image, "wallpaper4", src, dest);
	uiComponents.push_back(button);

	//join
	TextUI::setTextSize("Arialbd_20", "Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w) - (dest.w + 200);
	dest.y = (Game::camera.h) - (dest.h + 50);
	button = new TextUI("join", UILabels::text, "Arialbd_20", dest, color, "Ready");
	button->addLinkedItem("address");
	button->addLinkedItem("name");
	//Check whether the address is proper!
	button->setAction([]() {

		LobbyScene::ready[0] = true; // 0 is always player 1
		LobbyScene::ready[1] = true;
		LobbyScene::ready[2] = true;
		LobbyScene::ready[3] = true;

		//REMOVE THIS WHEN READY'ING
		//SceneManager::changeScenes("gameScene", true);

		//Play Music
		Game::mixer->playMusic(AudioMixer::game_music);
		Mix_VolumeMusic(SDL_MIX_MAXVOLUME/8);

		//std::cout << "Address: " << value << std::endl;
	});
	uiComponents.push_back(button);

	//Back
	TextUI::setTextSize("Arialbd_20", "Back", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = 0 + (20);
	dest.y = (Game::camera.h) - (dest.h + 10);
	button = new TextUI("back", UILabels::text, "Arialbd_20", dest, color, "Back");
	button->setAction([]() {
		SceneManager::changeScenes("joinScene");
	});
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Team 1
	//---------------------------------------------------

	dest.w = 375;
	dest.h = 300;
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	src.w = 1920;
	src.h = 1080;
	src.x = 0;
	src.y = 0;
	button = new UI("team1_background", UILabels::image, "black_lowalpha", src, dest);
	uiComponents.push_back(button);

	TextUI::setTextSize("Arialbd_40", "Team 1", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) - 100;
	button = new TextUI("team1", UILabels::text, "Arialbd_40", dest, color, "Team 1");
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Player 1
	TextUI::setTextSize("Arialbd_20", "Player1", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 300;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player1_name", UILabels::text, "Arialbd_20", dest, color, "Player1");
	uiComponents.push_back(button);

	//Player 1 Hero Type
	TextUI::setTextSize("Arialbd_20", "Knight", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player1_type", UILabels::text, "Arialbd_20", dest, color, "Knight");
	uiComponents.push_back(button);

	//Player 1 Ready
	TextUI::setTextSize("Arialbd_20", "Not Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 100;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player1_ready", UILabels::text, "Arialbd_20", dest, color, "Not Ready");
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Player 2
	TextUI::setTextSize("Arialbd_20", "Player2", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 300;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player2_name", UILabels::text, "Arialbd_20", dest, color, "Player2");
	uiComponents.push_back(button);

	//Player 2 Hero Type
	TextUI::setTextSize("Arialbd_20", "Wizard", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player2_type", UILabels::text, "Arialbd_20", dest, color, "Wizard");
	uiComponents.push_back(button);

	//Player 2 Ready
	TextUI::setTextSize("Arialbd_20", "Not Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) - 100;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player2_ready", UILabels::text, "Arialbd_20", dest, color, "Not Ready");
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Team 2
	//---------------------------------------------------

	dest.w = 375;
	dest.h = 300;
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	src.w = 1920;
	src.h = 1080;
	src.x = 0;
	src.y = 0;
	button = new UI("team2_background", UILabels::image, "black_lowalpha", src, dest);
	uiComponents.push_back(button);

	TextUI::setTextSize("Arialbd_40", "Team 2", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) - 100;
	button = new TextUI("team2", UILabels::text, "Arialbd_40", dest, color, "Team 2");
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Player 3
	TextUI::setTextSize("Arialbd_20", "Player3", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 100;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player3_name", UILabels::text, "Arialbd_20", dest, color, "Player3");
	uiComponents.push_back(button);

	//Player 3 Hero Type
	TextUI::setTextSize("Arialbd_20", "Knight", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player3_type", UILabels::text, "Arialbd_20", dest, color, "Knight");
	uiComponents.push_back(button);

	//Player 3 Ready
	TextUI::setTextSize("Arialbd_20", "Not Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 300;
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	button = new TextUI("player3_ready", UILabels::text, "Arialbd_20", dest, color, "Not Ready");
	uiComponents.push_back(button);

	//---------------------------------------------------
	//Player 4
	TextUI::setTextSize("Arialbd_20", "Player4", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 100;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player3_name", UILabels::text, "Arialbd_20", dest, color, "Player4");
	uiComponents.push_back(button);

	//Player 4 Hero Type
	TextUI::setTextSize("Arialbd_20", "Wizard", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 200;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player3_type", UILabels::text, "Arialbd_20", dest, color, "Wizard");
	uiComponents.push_back(button);

	//Player 4 Ready
	TextUI::setTextSize("Arialbd_20", "Not Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w / 2) - (dest.w / 2) + 300;
	dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
	button = new TextUI("player3_ready", UILabels::text, "Arialbd_20", dest, color, "Not Ready");
	uiComponents.push_back(button);

	////*****************************************
	////How to change/set the text of a uiComponent!
	////*****************************************
	//TextUI* textui = (TextUI*) UI::getVectorUI(uiComponents, "player1_name");
	//textui->setColor(255, 0, 0, 255); //set the text to red
	//textui->changeText("New Player1");



	////Back
	//DynamicUI::setTextSize("Arial_12", "Lost Mines", &dest.w, &dest.h);
	////dest.w = 0, dest.h = 0; //Doesn't need to be set
	//dest.x = 0 + (20);
	//dest.y = (Game::camera.h) - (dest.h + 20);
	//button = new DynamicUI("back", UILabels::text, "Arial_12", dest, color, "Back");
	//button->setAction([]() {
	//	//SceneManager::changeScenes("joinScene");
	//});
	//uiComponents.push_back(button);

}

void LobbyScene::addPlayer(int value, std::string name, int class_type) {
	UI* button;
	SDL_Rect dest;
	dest = { 0,0,0,0 };
	SDL_Color color = { 255,255,255,255 };

	switch (value) {
	case 1:
	case 3:
		dest.y = (Game::camera.h / 2) - (dest.h / 2);
		break;
	case 2:
	case 4:
		dest.y = (Game::camera.h / 2) - (dest.h / 2) + 50;
		break;
	default:
		dest.y = 0;
		break;
	}

	TextUI::setTextSize("Arialbd_20", name, &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	if (value < 3) {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) - 300;
	}
	else {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) + 100;
	}
	button = new TextUI(name + "_name", UILabels::text, "Arialbd_20", dest, color, name);
	uiComponents.push_back(button);

	std::string class_name = "Empty";
	if (class_type == 1) {
		class_name = "Knight";
	}
	else {
		class_name = "Wizard";
	}
	TextUI::setTextSize("Arialbd_20", class_name, &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	if (value < 3) {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) - 200;
	}
	else {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) + 200;
	}
	button = new TextUI(name + "_type", UILabels::text, "Arialbd_20", dest, color, class_name);
	uiComponents.push_back(button);

	TextUI::setTextSize("Arialbd_20", "Not Ready", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	if (value < 3) {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) - 100;
	}
	else {
		dest.x = (Game::camera.w / 2) - (dest.w / 2) + 300;
	}
	button = new TextUI(name + "_ready", UILabels::text, "Arialbd_20", dest, color, "Not Ready");
	uiComponents.push_back(button);
}

void LobbyScene::handleEvents() {
	updateMouse();
	//if (SDL_IsTextInputActive()) {
		updateKeyboardInput();
	//}
	bool switchScenes = true;
	for (int i = 0; i < 4; i++) {
		if (!LobbyScene::ready[i]) {
			switchScenes = false;
		}
	}
	if (switchScenes) {
		std::cout << "All player are READY: Switching Scenes" << std::endl;
		SceneManager::changeScenes("gameScene", true);
	}
}
void LobbyScene::update() {
	if (SceneManager::getScene("gameScene") == nullptr) {
		std::cout << "Waiting for valid Scene pointer" << std::endl;
	} else {
		GameScene* gameScene = (GameScene*) SceneManager::getScene("gameScene");
		if (gameScene->isLocal) {
			if (gameScene->getGamepadAButton(1)) {
				LobbyScene::ready[0] = true;
			}
			if (gameScene->getGamepadAButton(2)) {
				LobbyScene::ready[1] = true;
			}
			if (gameScene->getGamepadAButton(3)) {
				LobbyScene::ready[2] = true;
			}
			if (gameScene->getGamepadAButton(4)) {
				LobbyScene::ready[3] = true;
			}
		}
	}

	//std::cout << "Update: ";
	for (int i = 0; i < 4; i++) {
		//std::cout << ready[i] << ",";
		std::string name = "player";
		name += std::to_string((i + 1));
		name += "_ready";
		//std::cout << name << std::endl;
		TextUI* ui = (TextUI*) UI::getVectorUI(uiComponents, name);
		if (ui != nullptr) {
			if (ready[i]) {
				//std::cout << "setting" << std::endl;
				ui->setColor(255, 0, 0, 255);
				ui->changeText("Ready");
			}
			else {
				ui->setColor(255, 255, 255, 255);
				ui->changeText("Not Ready");
			}
		}
	}
	//std::cout << std::endl;
}

void LobbyScene::render() {
	for (int i = 0; i < uiComponents.size(); i++) {
		uiComponents.at(i)->render();
	}
	//Labels -----------

	//------------------
}

void LobbyScene::loadScene() {
	//Nothing
}

void LobbyScene::loadData(std::vector<std::string> data) {
	//Do something with passed data;
	//std::cout << "Loaded with Data: " << std::endl;
	std::cout << data.size() << std::endl;
	std::string address = data.at(0);
	//std::cout << "Address: " << address << std::endl;
	std::string name = data.at(1);
	//std::cout << "Name: " << name << std::endl;
}

//Mouse
void LobbyScene::updateMouse() {
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

void LobbyScene::updateKeyboardInput() {
	if (currentInputEnabled == nullptr) {
		//std::cout << "nullptr" << std::endl;
		return;
	}
	currentInputEnabled->callActionFunctionUI();
}

int LobbyScene::getMouseX() {
	return mouse_x;
}

int LobbyScene::getMouseY() {
	return mouse_y;
}