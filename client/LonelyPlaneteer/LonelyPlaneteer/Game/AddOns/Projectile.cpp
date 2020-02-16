#include "Projectile.h"
#include "../../Engine/Game.h"
#include "../Classes/HeroType.h"
#include "../Enemy/Enemy.h"
#include "../../Engine/Physics/Collision.h"


Projectile::Projectile() : Entity(GameScene::manager){}
//direction 1 = up 2 = down 3 = left 4 = right
Projectile::Projectile(float x, float y, int d, int t) : Entity(GameScene::manager) {
	
	direction = d;
	team = t;
	this->addComponent<TransformComponent>(x, y, 16, 32, 1);
	this->addComponent<SpriteComponent>("FireBall");
	this->getComponent<SpriteComponent>().setSrc(0, 0);
	this->getComponent<SpriteComponent>().setDest(x, y, 1);
	this->addComponent<ColliderComponent>("FireBall");
	
	this->getComponent<ColliderComponent>().setColliderSize(16, 30);

	Animation fly = Animation(0, 1, 100);
	Animation explode = Animation(1, 3, 200);

	animations.emplace("Fly", fly);
	animations.emplace("Explode", explode);

	play("Fly");

	this->setLayer(topLayer);
	this->addGroup(projectileGroup);

	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);

	GameScene::manager.addNewEntity(this);
}

Projectile::~Projectile() {

	this->destroy();

}

void Projectile::update() {
	if (!bulletDead) {
		this->getComponent<ColliderComponent>().update();
		updatePosition();
	}


	//Animate the sprite
	/*this->getComponent<SpriteComponent>().setSrc(
		this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>((SDL_GetTicks() / animSpeed) % frames),
		animIndex * this->getComponent<TransformComponent>().height
	);*/




	/*if (hitTime != 0){
		if ((SDL_GetTicks() - hitTime) > (animSpeed*frames)) {
			this->~Projectile();
		}
	}*/

}

void Projectile::updatePosition() {
	TransformComponent *tc = &this->getComponent<TransformComponent>();
	float yVelocity = 0.0f;
	float xVelocity = 0.0f;
	int width = 32;
	int height = 16;
	switch(direction){
		case 1://up
			yVelocity = -1.0f;
			angle = 90.0;
			height = 32;
			width = 16;
			break;
		case 2://down
			yVelocity = 1.0f;
			angle = -90.0;
			height = 32;
			width = 16;
			break;
		case 3://left
			xVelocity = -1.0f;
			angle = 0;
			break;
		case 4://right
			xVelocity = 1.0f;
			angle = 180.0;
			break;
	}
	tc->position.x += xVelocity * bulletSpeed;
	tc->position.y += yVelocity * bulletSpeed;
	distTravelled += abs(xVelocity + yVelocity) * bulletSpeed;

	this->getComponent<SpriteComponent>().setDest(tc->position.x, tc->position.y, 1);
	this->getComponent<ColliderComponent>().setCollider(tc->position.x, tc->position.y, width, height);
	if (distTravelled >= range) {
		killBullet();
	}
}

void Projectile::draw() {
	if (!bulletDead) {
		SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();
		SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();
		SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture();
		if (this->isActive()) {
			TextureManager::Draw(tex, src, dest, angle);
		}
	}
}

void Projectile::play(const char* animName) {

	//frames = animations[animName].frames;
	//animIndex = animations[animName].index;
	//animSpeed = animations[animName].speed;

}

void Projectile::collisionResponse(Collision* collision) {
	if (!bulletDead)
	{
		switch (collision->type) {
			case CollisionType::fireball_player: {
				HeroType* h = dynamic_cast<HeroType*>(collision->other.get());
				if (h->getTeam() != team && !h->isRespawning()) {
					this->bulletSpeed = 0.0f;
					this->updatePosition();
					h->takeDamage(damage);
					Game::mixer->playRandomSound(AudioMixer::fireballPlayerImpactSounds);
					killBullet();
				}
				break;
			}
			case CollisionType::fireball_enemy: {
				Enemy *enemy = dynamic_cast<Enemy*>(collision->other.get());
				if (!enemy->getIsDead()) {
					this->bulletSpeed = 0.0f;
					this->updatePosition();
					enemy->takeDamage(damage);
					Game::mixer->playRandomSound(AudioMixer::impactBonesSounds);
					killBullet();
				}
				break;
			}
			case CollisionType::fireball_wall: {
				this->bulletSpeed = 0.0f;
				this->updatePosition();
				//Sound FX
				if (hitTime == 0) {
					//GameScene::mixer->ricochet->play();
					Game::mixer->fbWallImpact->play();
				}
				
				killBullet();
				break;
			}
			default:
				break;
		}
	}
}

void Projectile::killBullet() {

	//play("Explode");

	if (hitTime == 0) {
		hitTime = SDL_GetTicks();
	}

	bulletDead = true;
}