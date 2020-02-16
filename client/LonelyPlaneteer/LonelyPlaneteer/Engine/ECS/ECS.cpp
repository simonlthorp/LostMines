#include "ECS.h"
#include "Component.h"

void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

void Entity::setLayer(Layer mLayer)
{
	layer = mLayer;
	manager.addToLayer(this, mLayer);
}

void Manager::draw() {
	for (auto& e : entities) {
		if (e->hasComponent<SpriteComponent>()) {
			if (!e->getComponent<SpriteComponent>().getCulled()) {
				e->draw();
			}
		} else {
			e->draw();
		}
	}
}

void Manager::drawLayers() {
	std::array<std::vector<Entity*>, maxGroups>& sortedLayeredEntities = layeredEntities;
	for (auto& vec : sortedLayeredEntities)
	{
		for (auto& e : vec) {
			if (e->hasComponent<SpriteComponent>()) {
				if (!e->getComponent<SpriteComponent>().getCulled()) {
					e->draw();
				}
			} else {
				if (e != nullptr) {
					if (e->isActive()) {
						e->draw();
					}
				}
			}
		}
	}
}