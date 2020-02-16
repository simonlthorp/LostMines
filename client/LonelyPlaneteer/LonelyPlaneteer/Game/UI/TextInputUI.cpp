#include "TextInputUI.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/AssetManager/AssetManager.h"

TextInputUI::TextInputUI() {}

TextInputUI::TextInputUI(std::string id, UILabels type, std::string fontName, SDL_Rect position, SDL_Color color, std::string placeholder) : labelColor(color), labelPosition(position), labelInitialPosition(position), text(placeholder){
	labelFont = Game::assetManager.getFont(fontName);
	createTexture();

	//super call
	UI::setID(id);
	UI::setType(type);
	UI::setSrc(SDL_Rect());

	//UI(id, labelTexture, position, SDL_Rect());
}

TextInputUI::TextInputUI(std::string id, UILabels type, TTF_Font* ttfFont, SDL_Rect position, SDL_Color color, std::string placeholder) : labelColor(color), labelPosition(position), labelInitialPosition(position), labelFont(ttfFont), text(placeholder) {
	createTexture();

	//super call
	UI::setID(id);
	UI::setType(type);
	UI::setSrc(SDL_Rect());

	//UI(id, labelTexture, position, SDL_Rect());
}

TextInputUI::~TextInputUI() {}


void TextInputUI::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 h) {
	labelColor = { r, g, b, h };
	createTexture();
}

void TextInputUI::setColor(SDL_Color color) {
	labelColor = color;
	createTexture();
}

std::string TextInputUI::getText() {
	return text;
}

void TextInputUI::changeText(std::string newText) {
	text = newText;
	TTF_SizeText(labelFont, text.c_str(), &labelPosition.w, &labelPosition.h);
	createTexture();
	//resetPosition();
}

void TextInputUI::resetPosition() {
	labelPosition.x = (labelInitialPosition.x + (labelInitialPosition.w /2)) - (labelPosition.w / 2);
	labelPosition.y = (labelInitialPosition.y + (labelInitialPosition.h / 2)) - (labelPosition.h / 2);
}

void TextInputUI::setTextSize(std::string font, std::string text, int *w, int *h) {
	TTF_SizeText(Game::assetManager.getFont(font), text.c_str(), w, h);
	std::cout << "FONT TEXT SIZE: W->" << w << " H->" << h << std::endl;
}

void TextInputUI::createTexture() {
	SDL_Surface* surf = TTF_RenderText_Blended(labelFont, text.c_str(), labelColor);
	labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelPosition.w, &labelPosition.h);

	//super call
	UI::setTexture(labelTexture);
	UI::setDest(labelPosition);
}

void TextInputUI::enableTextInput() {
	std::cout << "Enabled Text" << std::endl;
	inputEnabled = true;
	SDL_StartTextInput();
}

void TextInputUI::disableTextInput() {
	std::cout << "Disabled Text" << std::endl;
	inputEnabled = false;
	SDL_StopTextInput();
}