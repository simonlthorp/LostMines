#include "Tile.h"

Tile::Tile(float x, float y, int tileType, layerLabels layer) : Entity(GameScene::manager) {
	int srcX = (tileType % 8) * 32;
	int srcY = (tileType / 8) * 32;

	this->addComponent<TransformComponent>(x, y, 32, 32, 1);
	this->addComponent<SpriteComponent>("tileset");
	this->getComponent<SpriteComponent>().setSrc(srcX, srcY);
	this->getComponent<SpriteComponent>().setDest(x, y, 1);

	this->setLayer(layer);
}

void Tile::draw() {
	SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture();
	SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();
	SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();

	TextureManager::Draw(this->getComponent<SpriteComponent>().getTexture(), this->getComponent<SpriteComponent>().getSrc(), this->getComponent<SpriteComponent>().getDest(), 0);
}

