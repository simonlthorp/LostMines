#include "DynamicUI.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/AssetManager/AssetManager.h"

DynamicUI::DynamicUI() {}
DynamicUI::~DynamicUI() {}

DynamicUI::DynamicUI(std::string id, UILabels type, std::string backgroundName, SDL_Rect backDest, std::string valueName, int amount, int increment) : backgroundDest(backDest), amount(amount), currentAmount(amount), increment(increment) {
	backgroundTexture = Game::assetManager.getTexture(backgroundName);
	valueTexture = Game::assetManager.getTexture(valueName);

	valueDestActual = backgroundDest;
	/*valueDestActual.w -= 20;
	valueDestActual.h -= 20;*/
	valueDestActual.w = 460 / 2;
	valueDestActual.h = 26 / 2;
	valueDestActual.x += ((backgroundDest.w / 2) - (valueDestActual.w / 2));
	valueDestActual.y += ((backgroundDest.h / 2) - (valueDestActual.h / 2));
	valueDestMaximum = valueDestActual;


	//valueDestActual = valueDestMaximum;
	//valueDestActual.w = 0;

	UI::setID(id);
	UI::setType(type);
	UI::setDest(backDest);
}

void DynamicUI::enableTitle(std::string fontName, int xDisplacement, int yDisplacement, SDL_Color color, std::string text) {
	titleFont = Game::assetManager.getFont(fontName);
	titlePosition = backgroundDest;
	setTextSize(fontName, text, &titlePosition.w, &titlePosition.h);

	titlePosition.x += xDisplacement + ((backgroundDest.w / 2) - (titlePosition.w / 2));
	titlePosition.y += yDisplacement + ((backgroundDest.h / 2) - (titlePosition.h / 2));
	titleColor = color;
	title = text;
	
	createTitleTexture();
	titleEnabled = true;
}

void DynamicUI::enableText(std::string fontName, int xDisplacement, int yDisplacement, SDL_Color color) {
	textFont = Game::assetManager.getFont(fontName);
	textPosition = backgroundDest;

	std::string currentStr = std::to_string(currentAmount);
	std::string amountStr = std::to_string(amount);
	text = "" + currentStr + " / " + amountStr;

	setTextSize(fontName, text, &textPosition.w, &textPosition.h);

	textPosition.x += xDisplacement + ((backgroundDest.w / 2) - (textPosition.w / 2));
	textPosition.y += yDisplacement + ((backgroundDest.h / 2) - (textPosition.h / 2));
	textColor = color;
	
	createTextTexture();
	textEnabled = true;
}

void DynamicUI::enableEmblem(std::string textureName, int xDisplacement, int yDisplacement) {
	emblemTexture = Game::assetManager.getTexture(textureName);
	emblemDest = backgroundDest;
	emblemDest.w = 50;
	emblemDest.h = 50;
	emblemDest.x += xDisplacement + ((backgroundDest.w / 2) - (emblemDest.w /* EMBLEM SIZE */ / 2));
	emblemDest.y += yDisplacement + ((backgroundDest.h / 2) - (emblemDest.y /* EMBLEM SIZE */ / 2));
	//titleColor = color;
	//title = text;

	//createTitleTexture();
	emblemEnabled = true;
}

//Value functions
bool DynamicUI::setVal(int value) {
	currentAmount = value;
	//std::cout << "Amount: " << currentAmount << " / " << amount;
	//Update Image!
	updateValueTexture();
	if (currentAmount <= 0) {
		return false;
	}
	return true;
}

int DynamicUI::getVal() {
	return currentAmount;
}

bool DynamicUI::decrementVal() {
	//std::cout << "Amount: " << currentAmount << " / " << amount;
	if (currentAmount <= 0) {
		return false; //failed to decrement
	}
	int decrementalValue = amount / increment;
	currentAmount -= decrementalValue;
	updateValueTexture();
	return true;
}

bool DynamicUI::incrementVal() {
	//std::cout << "Amount: " << currentAmount << " / " << amount;
	if (currentAmount >= amount) {
		return false; //failed to increment
	}
	int incrementalValue = amount / increment;
	currentAmount += incrementalValue;
	updateValueTexture();
	return true;
}

void DynamicUI::updateValueTexture() {
	//int width = (currentAmount / increment) * (valueDestMaximum.w / increment);
	int width = static_cast<int>(((float) currentAmount / (float) amount) * valueDestMaximum.w);
	
	valueDestActual.w = width;

	if (textEnabled) {
		std::string currentStr = std::to_string(currentAmount);
		std::string amountStr = std::to_string(amount);
		text = "" + currentStr + " / " + amountStr;
		changeText(text);
	}
}



void DynamicUI::render() {
	//std::cout << "DynamicUI Render called" << std::endl;

	//-------------------DISABLED FOR NOW!------------------------

	//TextureManager::Draw(backgroundTexture, nullptr, backgroundDest, 0.0); // src -> nullptr, takes in full image
	//TextureManager::Draw(valueTexture, nullptr, valueDestActual, 0.0); // src -> nullptr, takes in full image
	TextureManager::DrawFont(backgroundTexture, backgroundDest);
	TextureManager::DrawFont(valueTexture, valueDestActual);


	//-------------------DISABLED FOR NOW!------------------------

	if (titleEnabled) {
		TextureManager::DrawFont(titleTexture, titlePosition);
	}
	if (textEnabled) {
		TextureManager::DrawFont(textTexture, textPosition);
	}
	if (emblemEnabled) {
		TextureManager::DrawFont(emblemTexture, emblemDest);
	}
}

//void DynamicUI::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 h) {
//	labelColor = { r, g, b, h };
//	createTexture();
//}
//
//void DynamicUI::setColor(SDL_Color color) {
//	labelColor = color;
//	createTexture();
//}

void DynamicUI::setTextSize(std::string font, std::string text, int *w, int *h) {
	TTF_SizeText(Game::assetManager.getFont(font), text.c_str(), w, h);
	std::cout << "FONT TEXT SIZE: W->" << w << " H->" << h << std::endl;
}

void DynamicUI::setTextSize(TTF_Font* font, std::string text, int *w, int *h) {
	TTF_SizeText(font, text.c_str(), w, h);
	std::cout << "FONT TEXT SIZE: W->" << w << " H->" << h << std::endl;
}

void DynamicUI::changeTitleText(std::string newText) {
	title = newText;

	SDL_Rect initialPosition = titlePosition;

	TTF_SizeText(titleFont, text.c_str(), &titlePosition.w, &titlePosition.h);
	titlePosition.x = (initialPosition.x + (initialPosition.w / 2)) - (titlePosition.w / 2);
	titlePosition.y = (initialPosition.y + (initialPosition.h / 2)) - (titlePosition.h / 2);

	createTitleTexture();
}

void DynamicUI::changeText(std::string newText) {
	text = newText;

	SDL_Rect initialPosition = textPosition;

	TTF_SizeText(textFont, text.c_str(), &textPosition.w, &textPosition.h);
	textPosition.x = (initialPosition.x + (initialPosition.w / 2)) - (textPosition.w / 2);
	textPosition.y = (initialPosition.y + (initialPosition.h / 2)) - (textPosition.h / 2);

	createTextTexture();
}

void DynamicUI::createTitleTexture() {
	SDL_Surface* surf = TTF_RenderText_Blended(titleFont, title.c_str(), titleColor);
	titleTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(titleTexture, nullptr, nullptr, &titlePosition.w, &titlePosition.h);
}

void DynamicUI::createTextTexture() {
	SDL_Surface* surf = TTF_RenderText_Blended(textFont, text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textPosition.w, &textPosition.h);
}