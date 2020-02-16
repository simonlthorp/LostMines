#include "TestEntity.h"
#include "../../Engine/ECS/Component.h"

#define WANDER_RADIUS 300

TestEntity::TestEntity(float x, float y) : Entity(GameScene::manager), color(SDL_Color{255,0,0,255})
{
	//this->addComponent<TransformComponent>(x, y, 64, 64, 1);
	this->addComponent<TransformComponent>(x, y, 64, 64, 0.75f);
	this->addComponent<SpriteComponent>("Skeleton");
	this->addComponent<ColliderComponent>("Test Entity");
	this->getComponent<ColliderComponent>().setColliderSize(40, 50);
	this->getComponent<ColliderComponent>().setCollider(x, y);
	//this->addComponent<Input>();
	this->addGroup(enemiesGroup);
	this->setLayer(topLayer);

	this->getComponent<TransformComponent>().speed = 2;
	goalX = x;
	goalY = y;
	this->getComponent<SpriteComponent>().setDest(x, y, 1);
	this->setDynamic(true);
}

void TestEntity::update()
{
	this->SetColliderColor(255, 0, 0, 255);

	//only change the new goal when you reach the new one
	if (abs(goalX - this->getComponent<TransformComponent>().position.x) <= 10 && abs(goalY - this->getComponent<TransformComponent>().position.y) <= 10) {
		wander();
	}

	move();
}

void TestEntity::draw() {
	TransformComponent& transform = this->getComponent<TransformComponent>();
	SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();

	dest.h = static_cast<int>(dest.h *transform.fScale);
	dest.w = static_cast<int>(dest.w *transform.fScale);

	SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();
	SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture();

	//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
	TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider, this->color);

	TextureManager::Draw(tex, src, dest, 0);
}

void TestEntity::collisionResponse(Collision* collision) {
	this->SetColliderColor(255, 255, 255, 255);
}

void TestEntity::SetColliderColor(int r, int g, int b, int a) {
	this->color = SDL_Color{ static_cast<Uint8>(r), static_cast<Uint8>(b), static_cast<Uint8>(g), static_cast<Uint8>(a) };
}

void TestEntity::updatePosition() {
}

void TestEntity::wander() {
	TransformComponent * tc = &this->getComponent<TransformComponent>();
	float circleX, circleY;
	float angle;

	const int mapWidth = MAP_WIDTH;
	const int mapHeight = MAP_HEIGHT;

	angle = static_cast<float>(rand()) / static_cast<float>(M_PI * 3 / 2);

	circleX = cos(angle) * WANDER_RADIUS;
	circleY = sin(angle) * WANDER_RADIUS;

	//Don't let the AI path outside of the game area.
	if (tc->position.x + circleX < 0 || tc->position.x + circleX >= mapWidth) {
		circleX *= -1;
	}

	if (tc->position.y + circleY < 0 || tc->position.y + circleY >= mapHeight) {
		circleY *= -1;
	}

	goalX = tc->position.x + circleX;
	goalY = tc->position.y + circleY;
}

void TestEntity::move() {
	TransformComponent *  tc = &this->getComponent<TransformComponent>();
	SpriteComponent * sc = &this->getComponent<SpriteComponent>();

	float x = tc->position.x;
	float y = tc->position.y;

	if (x > goalX) {
		tc->velocity.x = -1;
	}

	if (x < goalX) {
		tc->velocity.x = 1;
	}

	if (y > goalY) {
		tc->velocity.y = -1;
	}

	if (y < goalY) {
		tc->velocity.y = 1;
	}

	if (x == goalX) {
		tc->velocity.x = 0;
	}

	if (y == goalY) {
		tc->velocity.y = 0;
	}

	x += tc->velocity.x * tc->speed;
	y += tc->velocity.y * tc->speed;

	setPosition(x, y);
}

void TestEntity::setPosition(float x, float y) {
	this->getComponent<ColliderComponent>().setCollider(x, y);
	this->getComponent<TransformComponent>().setPos(x, y);
	this->getComponent<SpriteComponent>().setDest(x, y, this->getComponent<TransformComponent>().scale);
}
