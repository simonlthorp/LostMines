#include "Wall.h"

Wall::Wall(SDL_Texture* texture, float x, float y) : Entity(GameScene::manager) {
	int sc;
	float destX, destY;
	//Add components
	this->addComponent<TransformComponent>(x, y, 32, 32, 1);
	this->addComponent<SpriteComponent>(texture);
	this->addComponent<ColliderComponent>("Wall");
	this->addGroup(wallGroup);
	this->setLayer(topLayer);

	//std::cout << "Updating Transform" << std::endl;
	//set destination Rect for Sprite
	destX = this->getComponent<TransformComponent>().position.x;
	destY = this->getComponent<TransformComponent>().position.y;
	sc = this->getComponent<TransformComponent>().scale;
	//std::cout << "Updating Sprite" << std::endl;
	this->getComponent<SpriteComponent>().setSrc((221 % 8) * 32, (221 / 8) * 32);
	this->getComponent<SpriteComponent>().setDest(x, y, sc);
	//std::cout << "Finished" << std::endl;
}

void Wall::update() {
	TransformComponent *tc = &this->getComponent<TransformComponent>();
	this->getComponent<ColliderComponent>().updateCollider();
}

//draws sprite
void Wall::draw() {
	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
	SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();
	SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();
	SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture();
	TextureManager::Draw(tex, src, dest, 0);
	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
}

//sets position
void Wall::setPosition(float x, float y) {
	this->getComponent<TransformComponent>().setPos(x, y);
	this->getComponent<SpriteComponent>().setDest(x, y, this->getComponent<TransformComponent>().scale);
	TransformComponent* tc = &this->getComponent<TransformComponent>();
	//this->getComponent<ColliderComponent>().setCollider(tc->position.x, tc->position.y);
}

