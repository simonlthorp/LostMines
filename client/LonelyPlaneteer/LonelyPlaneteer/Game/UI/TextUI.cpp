#include "TextUI.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"
#include "../../Engine/AssetManager/AssetManager.h"

TextUI::TextUI() {}

TextUI::TextUI(std::string id, UILabels type, std::string fontName, SDL_Rect position, SDL_Color color, std::string text) : labelColor(color), labelPosition(position), text(text) {
	labelFont = Game::assetManager.getFont(fontName);
	createTexture();
	
	//super call
	UI::setID(id);
	UI::setType(type);
	UI::setSrc(SDL_Rect());

	//UI(id, labelTexture, position, SDL_Rect());
}

TextUI::TextUI(std::string id, UILabels type, TTF_Font* ttfFont, SDL_Rect position, SDL_Color color, std::string text) : labelColor(color), labelPosition(position), labelFont(ttfFont), text(text) {
	createTexture();
	
	//super call
	UI::setID(id);
	UI::setType(type);
	UI::setSrc(SDL_Rect());

	//UI(id, labelTexture, position, SDL_Rect());
}

TextUI::~TextUI() {}


void TextUI::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 h) {
	labelColor = { r, g, b, h };
	createTexture();
}

void TextUI::setColor(SDL_Color color) {
	labelColor = color;
	createTexture();
}

void TextUI::changeText(std::string newText) {
	text = newText;
	TTF_SizeText(labelFont, text.c_str(), &labelPosition.w, &labelPosition.h);
	createTexture();
}

void TextUI::setTextSize(std::string font, std::string text, int *w, int *h) {
	TTF_SizeText(Game::assetManager.getFont(font), text.c_str(), w, h);
	std::cout << "FONT TEXT SIZE: W->" << w << " H->" << h << std::endl;
}

void TextUI::createTexture() {
	SDL_Surface* surf = TTF_RenderText_Blended(labelFont, text.c_str(), labelColor);
	labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelPosition.w, &labelPosition.h);

	//super call
	UI::setTexture(labelTexture);
	UI::setDest(labelPosition);
}