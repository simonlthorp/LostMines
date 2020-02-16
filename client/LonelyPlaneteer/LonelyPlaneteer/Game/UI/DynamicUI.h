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

class DynamicUI : public UI {
public:
	DynamicUI();
	~DynamicUI();

	/*
		Background goes behind texture (aka. amount image values)
		Texture is slightly smaller than Background image size
	*/
	DynamicUI(std::string id, UILabels type, std::string backgroundName, SDL_Rect backDest, std::string valueName, int amount, int increment);
	void enableTitle(std::string fontName, int xDisplacement, int yDisplacement, SDL_Color color, std::string text);
	void enableText(std::string fontName, int xDisplacement, int yDisplacement, SDL_Color color);
	void enableEmblem(std::string textureName, int xDisplacement, int yDisplacement);

	void render() override;

	//Value functions
	bool setVal(int value); //Must be within amount value
	int getVal();
	bool decrementVal();
	bool incrementVal();
	void updateValueTexture();



	//Not Changed
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 h);
	void setColor(SDL_Color color);
	void changeTitleText(std::string newText);
	void changeText(std::string newText);
	static void setTextSize(std::string font, std::string text, int *w, int *h);
	static void setTextSize(TTF_Font* font, std::string text, int *w, int *h);

private:
	// Amount values
	int increment;
	int currentAmount = 0;
	int amount;

	//------- Title --------
	TTF_Font* titleFont;
	SDL_Texture* titleTexture;
	SDL_Color titleColor;
	SDL_Rect titlePosition;
	std::string title;
	bool titleEnabled = false;
	
	//------- Text ---------
	TTF_Font* textFont;
	SDL_Texture* textTexture;
	SDL_Color textColor;
	SDL_Rect textPosition;
	std::string text;
	bool textEnabled = false;

	//------- Emblem -------
	SDL_Texture* emblemTexture;
	SDL_Rect emblemSrc;
	SDL_Rect emblemDest;
	bool emblemEnabled = false;

	//------- Background -------
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundSrc;
	SDL_Rect backgroundDest;

	//------- Value -------
	SDL_Texture* valueTexture;
	SDL_Rect valueSrc;
	SDL_Rect valueDestActual;
	SDL_Rect valueDestMaximum;


	void createTitleTexture();
	void createTextTexture();
};