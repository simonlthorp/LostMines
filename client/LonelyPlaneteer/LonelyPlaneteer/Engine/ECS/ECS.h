#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "SDL.h"

class Component;
class Entity;
class Manager;
struct Collision;

using ComponentID = std::size_t;
using Group = std::size_t;
using Layer = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;
constexpr std::size_t maxLayers = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity {
protected:
	Manager& manager;
	bool active = true;
	bool dynamic = false;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
	
	Layer layer;


public:
	Entity(Manager& mManager, Layer mLayer = 0) : manager(mManager), layer(mLayer) {}

	virtual void update() {}

	virtual void lateUpdate() {}

	virtual void draw() {}

	virtual void collisionResponse(Collision* collision) {}

	bool isActive() { return active; }

	void destroy() { active = false; }

	bool hasGroup(Group mGroup) {
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);

	void deleteGroup(Group mGroup) {
		groupBitSet[mGroup] = false;
	}

	void setLayer(Layer mLayer);

	Layer getLayer(Layer mLayer) {
		return layer;
	}

	void setDynamic(bool mDynamic) { 
		dynamic = mDynamic; 
	}	
	
	bool isDynamic() { 
		return dynamic; 
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
	std::array<std::vector<Entity*>, maxLayers> layeredEntities;

public:
	void update() {
		for (auto& e : entities) {
			e->update();
		}
	}

	void lateUpdate() {
		for (auto& e : entities) {
			e->lateUpdate();
		}
	}

	void draw();

	void drawLayers();

	void refresh() {
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}), 
			std::end(entities));
	}

	void addToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	void addToLayer(Entity* mEntity, Layer mLayer)
	{
		layeredEntities[mLayer].emplace_back(mEntity);
	}

	Entity& addEntity() {
		Entity *e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	Entity& addNewEntity( Entity *e) {
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	auto& getEntities() { return entities; };
};
