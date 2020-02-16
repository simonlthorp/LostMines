#pragma once
//C++ Includes
#include <string>
//SDL includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//ENGINE includes
#include "UI.h"
//Game Includes

class TextInputUI : public UI {
public:
	TextInputUI();
	TextInputUI(std::string id, UILabels type, std::string fontName, SDL_Rect position, SDL_Color color, std::string placeholder);
	TextInputUI(std::string id, UILabels type, TTF_Font* ttfFont, SDL_Rect position, SDL_Color color, std::string placeholder);
	~TextInputUI();

	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 h);
	void setColor(SDL_Color color);
	std::string getText();
	void changeText(std::string newText);
	static void setTextSize(std::string font, std::string text, int *w, int *h);
	void resetPosition();
	void enableTextInput();
	void disableTextInput();
	bool inputEnabled = false;
	bool keyDown = false;
private:
	void createTexture();

	//------ Label -------
	TTF_Font* labelFont;
	SDL_Texture* labelTexture;
	SDL_Color labelColor;
	SDL_Rect labelPosition;
	SDL_Rect labelInitialPosition;
	//------ Label -------
	std::string text;
};