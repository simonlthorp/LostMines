#include "UI.h"
#include "../../Engine/Game.h"
#include "../../Engine/Texture/TextureManager.h"

UI::UI() {}

//param textureName - should only be used by non-ttf_font types
UI::UI(std::string id, UILabels type, std::string textureName, SDL_Rect src, SDL_Rect dest) : id(id), type(type), src(src), dest(dest) {
	//std::cout << "Creating UI -> ID: " << id << std::endl;
	texture = Game::assetManager.getTexture(textureName);
}

//Can be used by both images and fonts
UI::UI(std::string id, UILabels type, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) : id(id), type(type), texture(texture), src(src), dest(dest) {}

UI::~UI() {}

void UI::setAction(void (otherfunction) ()) {
	function = otherfunction;
	//Maybe
}

void UI::setActionForInput(void (otherfunction)(std::vector<UI*> ui)) {
	inputfunction = otherfunction;
	//Maybe
}

void UI::setType(UILabels newType) {
	type = newType;
}

void UI::setTexture(SDL_Texture* newTexture) {
	texture = newTexture;
}

void UI::setPosition(int x, int y) {
	dest.x = x;
	dest.y = y;
}

void UI::setSrc(SDL_Rect newSrc) {
	src = newSrc;
}

void UI::setDest(SDL_Rect newDest) {
	dest = newDest;
}

void UI::setID(std::string newID) {
	id = newID;
}

void UI::render() {
	switch (type) {
	case UILabels::linkedText:
	case UILabels::text:
		TextureManager::DrawFont(texture, dest);
		break;
	case UILabels::inputText:
		TextureManager::DrawFont(texture, dest);
		break;
	case UILabels::linkedImage:
	case UILabels::image:
		TextureManager::Draw(texture, src, dest, 0.0);
		break;
	case UILabels::dynamicUI:
		break;
	default:
		TextureManager::Draw(texture, src, dest, 0.0);
		break;
	}
}

SDL_Rect UI::getSrc() {
	return src;
}

SDL_Rect UI::getDest() {
	return dest;
}

SDL_Texture* UI::getTexture() {
	return texture;
}

std::string UI::getID() {
	return id;
}

UILabels UI::getType() {
	return type;
}

bool UI::withinUI(int x, int y) {
	int heightMIN = dest.y; //Bottom
	int heightMAX = dest.y + (dest.h); //Top
	int widthMIN = dest.x; //Left
	int widthMAX = dest.x + (dest.w); //Right

	if (x >= widthMIN && x <= widthMAX) {
		if (y >= heightMIN && y <= heightMAX) {
			return true;
		}
	}
	return false;
}

void UI::callActionFunction() {
	//std::cout << "Calling Action!" << std::endl;
	(function)();
}

void UI::callActionFunctionUI() {
	std::vector<UI*> list;
	list.push_back(this);
	(inputfunction)(list);
}

void UI::callActionFunctionUI(std::vector<UI*> evaluatedUIList) {
	(inputfunction)(evaluatedUIList);
}

std::vector<std::string> UI::getLinkedItems() {
	return linkedItems;
}

void UI::addLinkedItem(std::string value) {
	linkedItems.push_back(value);
}




UI* UI::getVectorUI(std::vector<UI*> list, std::string id) {
	std::vector<UI*>::iterator it = std::find_if(list.begin(), list.end(), [&](UI* ui) {
		return ui->getID() == id;
	});
	if (it == list.end()) {
		return nullptr;
	}
	UI* val = list.at(std::distance(list.begin(), it));
	return val;
}

std::vector<UI*> UI::getVectorUI(std::vector<UI*> list, std::vector<std::string> ids) {
	std::vector<UI*> values = std::vector<UI*>();
	for (std::string id : ids) {
		std::vector<UI*>::iterator it = std::find_if(list.begin(), list.end(), [&](UI* ui) {
			return ui->getID() == id;
		});
		if (it == list.end()) {
			//values.push_back(nullptr);
		}
		values.push_back(list.at(std::distance(list.begin(), it)));
	}
	return values;
}