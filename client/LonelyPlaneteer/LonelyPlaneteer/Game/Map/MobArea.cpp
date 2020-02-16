#include "MobArea.h"


MobArea::MobArea(float x, float y, int w, int h) : Entity(GameScene::manager) {
	this->addComponent<TransformComponent>(x, y);
	this->addComponent<ColliderComponent>("MobArea");
	this->getComponent<ColliderComponent>().setCollider(x, y, w, h);
	respawnPoint = RespawnPoint(x, y);
	topLeftX = x - w / 2;
	topLeftY = y - h / 2;
	btmRightX = x + w / 2;
	btmRightY = y + w / 2;
	addGroup(mobArea);
	this->setLayer(topLayer);
}

void MobArea::update() {
	TransformComponent tc = this->getComponent<TransformComponent>();
	this->getComponent<ColliderComponent>().setCollider(tc.position.x, tc.position.y);
}

void MobArea::draw() {
	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider, { 0,0,255 });
}