#pragma once
//SDL Includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//C++ Includes
#include <string>
#include <vector>

enum UILabels : std::size_t {
	text,
	linkedText,
	image,
	linkedImage,
	inputText,
	dynamicUI
	//buttonText, //extras
	//buttonImage //extras
};

class UI {
public:
	UI();
	UI(std::string id, UILabels type, std::string textureName, SDL_Rect src, SDL_Rect dest);
	UI(std::string id, UILabels type, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	~UI();

	void setAction(void (otherfunction)());
	void setActionForInput(void (otherfunction)(std::vector<UI*> ui));
	void setType(UILabels newType);
	void setTexture(SDL_Texture* newTexture);
	void setPosition(int x, int y);
	void setSrc(SDL_Rect newSrc);
	void setDest(SDL_Rect newDest);
	void setID(std::string newID);
	virtual void render();
	SDL_Rect getSrc();
	SDL_Rect getDest();
	SDL_Texture* getTexture();
	std::string getID();
	UILabels getType();
	bool withinUI(int x, int y);

	void callActionFunction();
	void callActionFunctionUI();
	void callActionFunctionUI(std::vector<UI*> evaluatedUIList);

	static UI* getVectorUI(std::vector<UI*> list, std::string id);
	static std::vector<UI*> getVectorUI(std::vector<UI*> list, std::vector<std::string> ids);
	std::vector<std::string> getLinkedItems();
	void addLinkedItem(std::string value);


protected:
	std::vector<std::string> linkedItems = std::vector<std::string>();
	void(*function)() = []() {};
	void(*inputfunction)(std::vector<UI*> ui) = [](std::vector<UI*> ui) {};
	std::string id;
	UILabels type;
	SDL_Rect src, dest;
	SDL_Texture* texture;
	bool state = false;
};