#pragma once
#include <string>
#include "SDL.h"
#include "../../Engine/ECS/ECS.h"
#include "../../Engine/ECS/Component.h"

class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent *transform;
	ColliderComponent(std::string t) {
		tag = t;
	}

	~ColliderComponent() {}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		collider.x = static_cast<int>(transform->position.x) - collider.w / 2;
		collider.y = static_cast<int>(transform->position.y) - collider.h / 2;

		if (transform->fScale != -1.0f)
		{
			collider.w = static_cast<int>(transform->width * transform->fScale);
			collider.h = static_cast<int>(transform->height * transform->fScale);
		}
		else
		{
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

	void update() override {
	}

	void updateCollider() {
		collider.x = static_cast<int>(transform->position.x) - collider.w / 2; 

		collider.y = static_cast<int>(transform->position.y) - collider.h / 2;
	}

	void setCollider(float x, float y) {
		if (transform->fScale != -1.0f) {
			collider.x = static_cast<int>(transform->position.x) - collider.w / 2;

			collider.y = static_cast<int>(transform->position.y) - collider.h / 2;
		} else	{
			collider.x = static_cast<int>(transform->position.x) - collider.w / 2;

			collider.y = static_cast<int>(transform->position.y) - collider.h / 2;
		}
	}

	void setCollider(float x, float y, int w, int h) {
		collider.w = w;
		collider.h = h;
		collider.x = static_cast<int>(transform->position.x) - collider.w / 2;

		collider.y = static_cast<int>(transform->position.y) - collider.h / 2;
	}

	void setColliderPosition(float x, float y, int xDiff, int yDiff) {
		collider.x = static_cast<int>(transform->position.x) - collider.w / xDiff;

		collider.y = static_cast<int>(transform->position.y) + collider.h / yDiff;
	}

	void setColliderSize(int w, int h) {
		if (transform->fScale != -1.0f)
		{
			collider.w = static_cast<int>(w * transform->fScale);
			collider.h = static_cast<int>(h * transform->fScale);
		}
		else
		{
			collider.w = w * transform->scale;
			collider.h = h * transform->scale;
		}
	}
};