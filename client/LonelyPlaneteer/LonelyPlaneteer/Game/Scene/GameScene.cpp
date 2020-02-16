#include "GameScene.h"
//Engine Includes
#include "../../Engine/Game.h"
#include "../../Engine/ECS/Vector2D.h"
#include "../../Engine/Quadtree/QuadtreeManager.h"
//Objects Includes
#include "../Objects/Player.h"
#include "../Objects/Wall.h"
#include "../Objects/TestEntity.h"
#include "../Classes/HeroType.h"
#include "../Classes/Knight.h"
#include "../Classes/Wizard.h"
#include "../Enemy/Enemy.h"
#include "../Objects/Mine.h"
#include "../Map/MobArea.h"
//Manager Includes
#include "../Map/MapManager.h"
#include "../Objects/MineManager.h"
#include "../Objects/MineManager.h"
//#include "Physics.h"
//#include "EnemyManager.h"
//UI Includes
#include "../UI/UI.h"
#include "../UI/DynamicUI.h"

#include "../UI/TextUI.h"

#include "../Objects/Tile.h"

#include <time.h>

Manager GameScene::manager;

//Audio
//AudioMixer* Game::mixer;
Mine* mine = nullptr;
Mine* mine2 = nullptr;
Mine* mine3 = nullptr;
Mine* mine4 = nullptr;
/*Mine* mine5 = nullptr;
Mine* mine6 = nullptr;
Mine* mine7 = nullptr;
Mine* mine8 = nullptr;*/
MineManager* mineManager = nullptr;
std::vector<Mine*> minesList;

Player *player = nullptr;
Player *player2 = nullptr;
Player *player3 = nullptr;
Player *player4 = nullptr;

Wall *wall = nullptr;
MapManager* mapM = nullptr;
Enemy *enemy = nullptr;

MobArea *mobArea1 = nullptr;
MobArea *mobArea2 = nullptr;
MobArea *mobArea3 = nullptr;
MobArea *mobArea4 = nullptr;

// Red Team Heroes
HeroType* redKnight = nullptr;
HeroType* redWizard = nullptr;

// Blue Team Heroes
HeroType* blueKnight = nullptr;
HeroType* blueWizard = nullptr;
GameScene::GameScene() {}
GameScene::~GameScene() {}

QuadtreeManager* qtm = nullptr;

TextUI* entityCountText = nullptr;

//Tile* tile = nullptr;


void GameScene::init() {
	isLocal = true;

	UI* button;
	SDL_Rect dest, src;
	SDL_Color color = { 255,255,255,255 };

	//------------------------------------- UI ------------------------------------------
	dest.w = 1920 * 6;
	dest.h = 1080 * 6;
	dest.x = (Game::camera.w / 2) - (dest.w / 2);
	dest.y = (Game::camera.h / 2) - (dest.h / 2);
	src.w = 1920;
	src.h = 1080;
	src.x = 0;
	src.y = 0;
	background = new UI("background", UILabels::image, "black", src, dest);


	
	SDL_Rect blue;
	/*
	blue.w = 495 / 2;
	blue.h = 68 / 2;
	blue.x = (Game::camera.w / 2) - (blue.w / 2);
	blue.y = (Game::camera.h) - (blue.h);
	
	DynamicUI* dynamic = new DynamicUI("health", UILabels::dynamicUI, "emblem_empty", blue, "emblem_red", 100, 10);
	dynamic->enableTitle("Arialbd_20", 0, -10, color, "Health");
	dynamic->enableText("Arial_12", 0, 10, color);
	dynamic->setVal(100);
	button = dynamic;
	//button->setActionForInput([](std::vector<UI*> ui) {
	//	DynamicUI* dyn = (DynamicUI*)ui.at(0);
	//	//dyn->decrementVal();
	//	dyn->decrementVal();
	//});
	uiComponents.push_back(button);

	*/
	blue.w = 495 / 2;
	blue.h = 68 / 2;
	blue.x = (Game::camera.w / 2) - (blue.w / 2) - 200;
	blue.y = 0; //(Game::camera.h / 2) - (blue.h / 2) - 200;
	DynamicUI* dynamic = new DynamicUI("team1_score", UILabels::dynamicUI, "emblem_empty", blue, "emblem_blue", 1000, 100);
	dynamic->enableTitle("Arialbd_20", 0, -10, color, "Team 1");
	dynamic->enableText("Arial_12", 0, 10, color);
	dynamic->setVal(0);
	button = dynamic;
	//button->setActionForInput([](std::vector<UI*> ui) {
	//	DynamicUI* dyn = (DynamicUI*)ui.at(0);
	//	//dyn->decrementVal();
	//	dyn->incrementVal();
	//});
	uiComponents.push_back(button);

	blue.w = 495 / 2;
	blue.h = 68 / 2;
	blue.x = (Game::camera.w / 2) - (blue.w / 2) + 200;
	blue.y = 0; //(Game::camera.h / 2) - (blue.h / 2) - 200;
	dynamic = new DynamicUI("team2_score", UILabels::dynamicUI, "emblem_empty", blue, "emblem_blue", 1000, 100);
	dynamic->enableTitle("Arialbd_20", 0, -10, color, "Team 2");
	dynamic->enableText("Arial_12", 0, 10, color);
	dynamic->setVal(0);
	button = dynamic;
	//button->setActionForInput([](std::vector<UI*> ui) {
	//	DynamicUI* dyn = (DynamicUI*)ui.at(0);
	//	//dyn->decrementVal();
	//	dyn->incrementVal();
	//});
	uiComponents.push_back(button);

	TextUI::setTextSize("Arialbd_20", "Back", &dest.w, &dest.h);
	//dest.w = 0, dest.h = 0; //Doesn't need to be set
	dest.x = (Game::camera.w) - (dest.w + 20);
	dest.y = (dest.h / 2);
	button = new TextUI("back", UILabels::text, "Arialbd_20", dest, color, "Back");
	button->setAction([]() {
		Game::resetCamera();
		SceneManager::changeScenes("menuScene");
	});
	uiComponents.push_back(button);
	//------------------------------------- UI ------------------------------------------

	mapM = new MapManager();

	//tile = new Tile(-64, -64, 199);
	//GameScene::manager.addNewEntity(tile);

	SDL_Rect center = mapM->getCenterPoint();   // center point

	// SET GAME RULES
	setMaxPoints(1000);

	// *** The following Mines are ordered from Left to Right ***
	// Mine constructor (Xpos, Ypos, ID, CLASS, ACTIVE, TIME IN MilliSec)
	/*mine = new Mine(304, 3490, 0, 0, true, 5000);     // Bottom Left corner mine
	mine2 = new Mine(812, 3104, 1, 1, false, 5000);    // 2nd mine
	mine3 = new Mine(1326, 2720, 2, 0, false, 5000);   // 3rd mine
	mine4 = new Mine(1856, 2328, 3, 1, false, 5000);   // 4th mine

	mine5 = new Mine(3120, 1440, 4, 0, false, 5000);     // 5th mine. (first mine on the right half of the map)
	mine6 = new Mine(3632, 1056, 5, 1, false, 5000);     // 6th mine
	mine7 = new Mine(4144, 672, 6, 0, false, 5000);    // 7th mine
	mine8 = new Mine(4688, 296, 7, 1, false, 5000);     // Top Right corner mine (Rightmost mine)*/

	mine = new Mine(135, 901, 0, 0, false);     // X, Y, PLAYER TYPE, ACTIVE/NOT ACTIVE, TIME IN MilliSec
	mine2 = new Mine(546, 769, 1, 1, false);   // bottom center mine
	mine3 = new Mine(1458, 226, 2, 0, false);   // left side mine
	mine4 = new Mine(1767, 103, 3, 1, false);  // right side mine

	minesList.push_back(mine);
	minesList.push_back(mine2);
	minesList.push_back(mine3);
	minesList.push_back(mine4);

	/*minesList.push_back(mine5);
	minesList.push_back(mine6);
	minesList.push_back(mine7);
	minesList.push_back(mine8); */

	mineManager = new MineManager(minesList);

	//creates player teams and entities
	if (isLocal){
		createTeamsLocal();
	} else {
		createTeams();
	}
	
	std::vector<Player*> ps;
	ps.push_back(player);

	if (isLocal) {
		ps.push_back(player2);
		ps.push_back(player3);
		ps.push_back(player4);
	}

	std::vector<MobArea*> mb;
	mobArea1 = new MobArea(990, 525, 400, 400);
	mb.push_back(mobArea1);
	

	const int enemyCount = 32;
	int windowX;
	int windowY;
	SDL_GetWindowSize(Game::window, &windowX, &windowY);

	GameScene::manager.addNewEntity(mine); 
	GameScene::manager.addNewEntity(mine2);
	GameScene::manager.addNewEntity(mine3);
	GameScene::manager.addNewEntity(mine4);
	/*GameScene::manager.addNewEntity(mine5);
	GameScene::manager.addNewEntity(mine6);
	GameScene::manager.addNewEntity(mine7);
	GameScene::manager.addNewEntity(mine8);*/
	GameScene::manager.addNewEntity(mineManager);
	GameScene::manager.addNewEntity(mobArea1);

	for (int i = 0; i < 10; i++) {
		enemy = new Enemy(ps, mb);
		GameScene::manager.addNewEntity(enemy);
	}

	mapM->drawAllColiders();

	MapData* md = mapM->getMap();
	qtm = new QuadtreeManager(md->width + 2, md->height + 2, 32);
	SDL_Color labelColor = { 255, 255, 255, 255 };
	entityCountText = new TextUI("entityCountText", UILabels::text, "Arial_12", SDL_Rect{10, 40}, labelColor, "00");
}

void GameScene::createTeams() {
	int playerTeam = 1; // 1 = red, 2 = blue
	int playerClass = 1; // 1 = knight,  2 = wizard

	//Red Team
	redKnight = new Knight(1);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	redWizard = new Wizard(1);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	
	// redWizard->addToScore(400);   // JUST A TEST FOR SINGLE PLAYER

	//Blue Team
	blueKnight = new Knight(2);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	blueWizard = new Wizard(2);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.

	if (playerTeam == 1) {
		//Red Team
		switch (playerClass) {
		case 1:
			player = new Player(redKnight, isLocal);
			GameScene::manager.addNewEntity(redWizard);
			GameScene::manager.addNewEntity(redKnight);
			break;
		case 2:
			player = new Player(redWizard, isLocal);
			GameScene::manager.addNewEntity(redKnight);
			GameScene::manager.addNewEntity(redWizard);
			break;
		default:
			player = new Player(redKnight, isLocal);
			GameScene::manager.addNewEntity(redWizard);
			GameScene::manager.addNewEntity(redKnight);
			break;
		}
		GameScene::manager.addNewEntity(blueKnight);
		GameScene::manager.addNewEntity(blueWizard);
		
	} else {
		//blue Team
		switch (playerClass) {
		case 1:
			player = new Player(blueKnight, isLocal);
			GameScene::manager.addNewEntity(blueKnight);
			GameScene::manager.addNewEntity(blueWizard);
			break;

		case 2:
			player = new Player(blueWizard, isLocal);
			GameScene::manager.addNewEntity(blueWizard);
			GameScene::manager.addNewEntity(blueKnight);
			break;

		default:
			player = new Player(blueKnight, isLocal);
			GameScene::manager.addNewEntity(blueKnight);
			GameScene::manager.addNewEntity(blueWizard);
			break;
		}
		GameScene::manager.addNewEntity(redKnight);
		GameScene::manager.addNewEntity(redWizard);
	}
	GameScene::manager.addNewEntity(player);
}

void GameScene::createTeamsLocal() {
	//srand(static_cast<unsigned>(time(NULL)));

	int playerTeam = rand() % 2; // 1 = red, 2 = blue
	int playerClass = rand() % 2; // 1 = knight,  2 = wizard
	
	//std::cout << "team: " << playerTeam << ", class: " << playerClass << std::endl;

	//Red Team
	redKnight = new Knight(1);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	redWizard = new Wizard(1);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	
	// redWizard->addToScore(400);   // JUST A TEST FOR SINGLE PLAYER

	//Blue Team
	blueKnight = new Knight(2);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.
	blueWizard = new Wizard(2);    // Changed, now initialized as a null ptr in the Header file so it can be a class variable.

	if (playerTeam == 1) {
		if (playerClass == 1) {
			player = new Player(redKnight, isLocal);
			player2 = new Player(redWizard, isLocal);

			player3 = new Player(blueKnight, isLocal);
			player4 = new Player(blueWizard, isLocal);
		} else {
			player = new Player(redWizard, isLocal);
			player2 = new Player(redKnight, isLocal);

			player3 = new Player(blueWizard, isLocal);
			player4 = new Player(blueKnight, isLocal);
		}
	} else {
		if (playerClass == 1) {
			player = new Player(blueKnight, isLocal);
			player2 = new Player(blueWizard, isLocal);

			player3 = new Player(redKnight, isLocal);
			player4 = new Player(redWizard, isLocal);
		} else {
			player = new Player(blueWizard, isLocal);
			player2 = new Player(blueKnight, isLocal);

			player3 = new Player(redWizard, isLocal);
			player4 = new Player(redKnight, isLocal);
		}
	}


	GameScene::manager.addNewEntity(redKnight);
	GameScene::manager.addNewEntity(redWizard);
	GameScene::manager.addNewEntity(blueKnight);
	GameScene::manager.addNewEntity(blueWizard);
	GameScene::manager.addNewEntity(player);
	GameScene::manager.addNewEntity(player2);
	GameScene::manager.addNewEntity(player3);
	GameScene::manager.addNewEntity(player4);
}

void GameScene::setGameOverState(bool display) {
	if (display && gameOverText == nullptr) {
		SDL_Rect dest;
		SDL_Color color = { 255,0,0,255 };

		std::string text = "";
		if (redScore > blueScore) {
			text = "Game Over: Team 1 Wins";
		}
		else if (blueScore > redScore) {
			text = "Game Over: Team 2 Wins";
		}
		else {
			text = "Game Over: Tie Game";
		}

		TextUI::setTextSize("Arialbd_40", text, &dest.w, &dest.h);
		//dest.w = 0, dest.h = 0; //Doesn't need to be set
		dest.x = (Game::camera.w / 2) - (dest.w / 2);
		dest.y = (Game::camera.h / 2) - (dest.h / 2);
		gameOverText = new TextUI("gameover", UILabels::text, "Arialbd_40", dest, color, text);
		resetScore();
		//gameOverText->setAction([]() {
		//	Game::resetCamera();
		//	SceneManager::changeScenes("menuScene");
		//});
	}
	else if (!display) {
		gameOverText = nullptr;
	}
}

void GameScene::setMaxPoints(int maxScore) {
	goal = maxScore;
}

// Returns TRUE if Game is Over.
bool GameScene::checkForWinner() {
	return blueScore >= goal || redScore >= goal ? true : false;
}


// Resets the team scores and individual hero scores.
void GameScene::resetScore() {
	if (redKnight != nullptr)
		redKnight->resetScore();

	if (redWizard != nullptr)
		redWizard->resetScore();

	if (blueKnight != nullptr)
		blueKnight->resetScore();

	if (blueWizard != nullptr)
		blueWizard->resetScore();

	redScore = 0;
	blueScore = 0;
}


// Updates the Team Scores
void GameScene::updateScore() {
	if (!checkForWinner()) {
		if (redKnight != nullptr && redWizard != nullptr) {
			redScore = static_cast<int>(redKnight->getPlayerScore() + redWizard->getPlayerScore());
			//std::cout << "Red Score: " << redScore << std::endl;
		}

		if (blueKnight != nullptr && blueWizard != nullptr) {
			blueScore = static_cast<int>(blueKnight->getPlayerScore() + blueWizard->getPlayerScore());
			//std::cout << "Blue Score: " << blueScore << std::endl;
		}

		DynamicUI* teamScoreUI = (DynamicUI*)uiComponents[0];
		teamScoreUI->setVal(redScore);
		teamScoreUI = (DynamicUI*)uiComponents[1];
		teamScoreUI->setVal(blueScore);
	}
}



void GameScene::handleEvents() {
	player->eventHandle();
	updateMouse();


}

void GameScene::update() {
	GameScene::manager.update();

	//Update the Team Scores
	updateScore();

	/*
	SpriteComponent& playerSpriteComponent = player->getPlyrClass()->getComponent<SpriteComponent>();
	int x = playerSpriteComponent.getDest().x + (playerSpriteComponent.getDest().w / 2);
	int y = playerSpriteComponent.getDest().y + (playerSpriteComponent.getDest().h / 2);
	Game::camera.x = x - (Game::camera.w / 2);
	Game::camera.y = y - (Game::camera.h / 2);
	*/


	const int spawnMultiplier = 10;

	if (keystates[SDL_SCANCODE_1]) {
		spawnNewTestEntity();
	}

	if (keystates[SDL_SCANCODE_2]) {
		for (int i = 0; i < spawnMultiplier; i++)
		{
			spawnNewTestEntity();
		}
	}
	entityCountText->changeText("Entity Count: " + std::to_string(manager.getEntities().size()));

	qtm->update();

	//DynamicUI* dynUI;
	//dynUI = (DynamicUI*) uiComponents[0];
	//dynUI->setVal(player->getHealth());

	// CHECK FOR WINNER TO END GAME
	if (checkForWinner()) {
		//winningTeam = getWinner();
		setGameOverState(true);
		//std::cout << " WINNER IS : " << (winningTeam == 1 ? "Red" : "Blue") << " Team" << std::endl;

		// DO SOMETHING HERE LIKE CHANGING SCENES TO A WINNER SCREEN...
	}
}

void GameScene::lateUpdate() {
	GameScene::manager.lateUpdate();
}

void GameScene::render() {
	
	//CAMERA RESET HERE!
	Game::camera.x = 0;
	Game::camera.y = 0;

	background->render();
	manager.drawLayers();
	qtm->draw();
	//player->uiManager->healthUI->draw();   // draw health bar
	entityCountText->render();
	
	//UI in front
	for (int i = 0; i < uiComponents.size(); i++) {
		uiComponents.at(i)->render();
	}

	if (gameOverText != nullptr) {
		gameOverText->render();
	}
}

void GameScene::spawnNewTestEntity()
{
	TestEntity *te = new TestEntity(400, 400);
	GameScene::manager.addNewEntity(te);
}

void GameScene::loadScene() {
	//Camera

	//player->draw();
	//manager.drawLayers();
	//qtm->debugDraw();
	//player->uiManager->healthUI->draw();   // draw health bar
}

//Mouse
void GameScene::updateMouse() {
	//Shoot at mouse cursor
	if (Game::event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_BUTTON_LEFT) && mouseDown == false) {
		mouseDown = true;
		if (SDL_GetMouseState(&mouse_x, &mouse_y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
			//left click
			//std::cout << getMouseX() << " " << getMouseY() << std::endl;
			for (int i = 0; i < uiComponents.size(); i++) {
				if (uiComponents.at(i)->withinUI(getMouseX(), getMouseY())) {
					if (uiComponents.at(i)->getType() == UILabels::inputText) {
						uiComponents.at(i)->callActionFunction();
						//std::cout << uiComponents.at(i)->getID() << std::endl;
					}
					else if (uiComponents.at(i)->getType() == UILabels::dynamicUI) {
						uiComponents.at(i)->callActionFunctionUI();
					}
					else {
						uiComponents.at(i)->callActionFunction();
					}
				}
			}
		}
	}
	else if (Game::event.type == SDL_MOUSEBUTTONUP && SDL_BUTTON(SDL_BUTTON_LEFT)) {
		mouseDown = false;
	}
}

int GameScene::getMouseX() {
	return mouse_x;
}

int GameScene::getMouseY() {
	return mouse_y;
}

bool GameScene::getGamepadAButton(int id) {
	//std::cout << "Get Button GamePad " << id << std::endl;
	player->getComponent<GamepadInput>().update();
	player2->getComponent<GamepadInput>().update();
	player3->getComponent<GamepadInput>().update();
	player4->getComponent<GamepadInput>().update();
	switch (id) {
	case 1:
		if (player->getComponent<GamepadInput>().a) {
			//std::cout << "Returning A: " << id << std::endl;
			return true;
		}
		break;
	case 2:
		if (player2->getComponent<GamepadInput>().a) {
			//std::cout << "Returning A: " << id << std::endl;
			return true;
		}
		break;
	case 3:
		if (player3->getComponent<GamepadInput>().a) {
			//std::cout << "Returning A: " << id << std::endl;
			return true;
		}
		break;
	case 4:
		if (player4->getComponent<GamepadInput>().a) {
			//std::cout << "Returning A: " << id << std::endl;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}