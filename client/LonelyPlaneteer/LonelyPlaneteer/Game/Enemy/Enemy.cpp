#include "Enemy.h"
#include <math.h>
#include <time.h>
//#include "Animation.h"
#include "../Map/MobArea.h"

Enemy::Enemy(std::vector<Player*> p, std::vector<MobArea*> m) : Entity(GameScene::manager) {
	//ColliderComponent mbc = m->getComponent<ColliderComponent>();
	mobAreas = m;
	mobArea = m[0];
	rp = mobArea->getRespawnPoint();
	int x = rp.getX();
	int y = rp.getY();

	this->addComponent<TransformComponent>(x, y, 64, 64, 1);
	this->addComponent<SpriteComponent>("Skeleton");
	this->addComponent<ColliderComponent>("Enemy");
	this->getComponent<ColliderComponent>().setColliderSize(40, 50);
	this->addComponent<SightComponent>();
	this->addComponent<HealthComponent>(20);

	
	this->addGroup(enemiesGroup);
	this->setLayer(topLayer);
	this->players = p;
	
	//sword = new Sword(rp.getX(), rp.getY(), this);

	this->getComponent<TransformComponent>().speed = 1;
	goalX = x;
	goalY = y;
	this->getComponent<SpriteComponent>().setDest(x, y, 1);

	state = EnemyState::WANDER;
	/*Animation walk = Animation(0, 8, 100);
	Animation attack = Animation(1, 5, 100);
	Animation explode = Animation(2, 6, 100);

	animations.emplace("Walk", walk);
	animations.emplace("Attack", attack);
	animations.emplace("Explode", explode);

	play("Walk");

	path = { -1, -1 };*/

	animator = new Animator();
	animator->addAnimation("idleUp", Animation(0, 1, 100));
	animator->addAnimation("idleLeft", Animation(1, 1, 100));
	animator->addAnimation("idleDown", Animation(2, 1, 100));
	animator->addAnimation("idleRight", Animation(3, 1, 100));
	animator->addAnimation("walkUp", Animation(4, 5, 50));
	animator->addAnimation("walkLeft", Animation(5, 5, 50));
	animator->addAnimation("walkDown", Animation(6, 5, 50));
	animator->addAnimation("walkRight", Animation(7, 5, 50));
	animator->addAnimation("attackUp", Animation(8, 5, 100));
	animator->addAnimation("attackLeft", Animation(9, 5, 100));
	animator->addAnimation("attackDown", Animation(10, 5, 100));
	animator->addAnimation("attackRight", Animation(11, 5, 100));
	animator->addAnimation("castUp", Animation(12, 9, 75));
	animator->addAnimation("castLeft", Animation(13, 9, 75));
	animator->addAnimation("castDown", Animation(14, 9, 75));
	animator->addAnimation("castRight", Animation(15, 9, 75));
	animator->addAnimation("death", Animation(16, 6, 100));

	animator->playAnimation("walkDown");
	facingDirection = directions::DOWN;

	// tells the quadtree this needs to be updated every frame
	this->setDynamic(true);
}

Enemy::~Enemy() {

	//std::cout << "Enemy Destroyed" << std::endl;

}

void Enemy::update() {
	if (!isDead) {
		bool seesPlayer = false;
		Player* p = nullptr;
		TransformComponent tc = this->getComponent<TransformComponent>();
		this->getComponent<ColliderComponent>().updateCollider();

		//Face towards your goal
		//face();

		//Calculates the forward vector for the enemy
		//this->getComponent<SightComponent>().calculateSightLine(&this->getComponent<TransformComponent>(), GIVE_UP_DISTANCE);

		for (Player *player : players) {
			if (this->getComponent<SightComponent>().canSeePlayer(&this->getComponent<TransformComponent>(), 
				&player->getTransformComponent(), GIVE_UP_DISTANCE)) {
				if (!player->getPlyrClass()->isRespawning()) {
					seesPlayer = true;
					p = player;
					break;
				}
			}
		}

		 if(seesPlayer){

			if (Physics::AABB(p->getClass()->getComponent<ColliderComponent>().collider, mobArea->getComponent<ColliderComponent>().collider)) {
				TransformComponent playerTc = p->getTransformComponent();
				TransformComponent enemyTc = this->getComponent<TransformComponent>();
				float x = abs(playerTc.position.x - enemyTc.position.x);
				float y = abs(playerTc.position.y - enemyTc.position.y);
				float distance = sqrt(x * x + y * y);

				if (distance <= attackDist) {
					state = EnemyState::ATTACK;
				}
				else if (distance >= attackDist) {
					//std::cout << "Chasing" << std::endl;
					state = EnemyState::CHASE;
				}
			} else {
				state = EnemyState::WANDER;
			}

		}
		else {
			state = EnemyState::WANDER;
		}

		switch (state) {
		case EnemyState::CHASE:
			chase(p);
			move();
			break;
		case EnemyState::ATTACK:
			attack(p);

			break;
		case EnemyState::PATROL:
			//patrol();
			break;
		case EnemyState::WANDER:
			//only change the new goal when you reach the new one
			if (abs(goalX - this->getComponent<TransformComponent>().position.x) <= 10 && abs(goalY - this->getComponent<TransformComponent>().position.y) <= 10) {
				wander();
			}
			move();
			break;
		default:
			break;
		}
	} else {
		respawn();
	}

	updateAnimation();
}

void Enemy::draw() {
	SDL_Rect goalRect;
	goalRect.x = goalX;
	goalRect.y = goalY;
	goalRect.w = 10;
	goalRect.h = 10;
	
	if (!isDead) {
		//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);
		//TextureManager::DrawRect(&sword->getComponent<ColliderComponent>().collider, { 0,0,0 });
		SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();//get destination rect
		SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();//get source rect 
		SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture(); // get the texture
		TextureManager::Draw(tex, src, dest, 0);

		float tmpX = this->getComponent<TransformComponent>().position.x + this->getComponent<SpriteComponent>().getDest().w / 2;
		float tmpY = this->getComponent<TransformComponent>().position.y + this->getComponent<SpriteComponent>().getDest().h / 2;

		TextureManager::DrawLine(0, 0, 255, static_cast<int>(this->getComponent<TransformComponent>().position.x),
			static_cast<int>(this->getComponent<TransformComponent>().position.y), static_cast<int>(tmpX), static_cast<int>(tmpY));

		
	}
	else if (isDead && (SDL_GetTicks() - timeOfDeath < animator->getAnimation(animator->getCurrent()).numberOfFrames * animator->getAnimation(animator->getCurrent()).msPerFrame)) {
		//TextureManager::DrawRect(&this->getComponent<ColliderComponent>().collider);

		SDL_Rect dest = this->getComponent<SpriteComponent>().getDest();//get destination rect
		SDL_Rect src = this->getComponent<SpriteComponent>().getSrc();//get source rect 
		SDL_Texture* tex = this->getComponent<SpriteComponent>().getTexture(); // get the texture
		TextureManager::Draw(tex, src, dest, 0);

		float tmpX = this->getComponent<TransformComponent>().position.x + this->getComponent<SpriteComponent>().getDest().w / 2;
		float tmpY = this->getComponent<TransformComponent>().position.y + this->getComponent<SpriteComponent>().getDest().h / 2;

		TextureManager::DrawLine(0, 0, 255, static_cast<int>(this->getComponent<TransformComponent>().position.x),
			static_cast<int>(this->getComponent<TransformComponent>().position.y), static_cast<int>(tmpX), static_cast<int>(tmpY));
	}
	//Draw enemy Goal
	/*SDL_Rect tar;
	tar.h = 32;
	tar.w = 32;
	tar.x = goalX;
	tar.y = goalY;
	TextureManager::DrawRect(&tar);*/
}

void Enemy::updatePosition() {}

void Enemy::updateAnimation() {

	if (isDead) {
		this->getComponent<SpriteComponent>().setSrc(
			this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>(((SDL_GetTicks()-timeOfDeath) / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
			animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
	}
	else
	{
		this->getComponent<SpriteComponent>().setSrc(
			this->getComponent<SpriteComponent>().getSrc().w * static_cast<int>((SDL_GetTicks() / animator->getAnimation(animator->getCurrent()).msPerFrame) % animator->getAnimation(animator->getCurrent()).numberOfFrames),
			animator->getAnimation(animator->getCurrent()).index * this->getComponent<TransformComponent>().height);
	}
}

void Enemy::setPosition(float x, float y) {
	this->getComponent<ColliderComponent>().setCollider(x, y);
	this->getComponent<TransformComponent>().setPos(x, y);
	this->getComponent<SpriteComponent>().setDest(x, y, this->getComponent<TransformComponent>().scale);
	//updateSwordPosition();
}

void Enemy::updateSwordPosition() {
	//sword->setPosition(this->getComponent<TransformComponent>().position.x, this->getComponent<TransformComponent>().position.y);
}

void Enemy::setPath(int x, int y) {
	this->path.x = x;
	this->path.y = y;
}

bool Enemy::getIsDead()
{
	return this->isDead;
}

void Enemy::move() {
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

void Enemy::chase(Player *player) {
	if (player == nullptr) {
		std::cerr << "Player is null!" << std::endl;
		return;
	} else {
		const TransformComponent pT = player->getTransformComponent();
		goalX = pT.position.x;
		goalY = pT.position.y;
	}
}

void Enemy::wander() {
	TransformComponent * tc = &this->getComponent<TransformComponent>();
	float circleX, circleY;
	float angle;

	SDL_Rect nextPos;

	//const int scale = mm->getMapScale();
	const int mapWidth = mobArea->getComponent<ColliderComponent>().collider.w; //mm->getMapWidth() * 32;
	const int mapHeight = mobArea->getComponent<ColliderComponent>().collider.h;//mm->getMapHeight() * 32;

	angle = static_cast<float>(rand()) / static_cast<float>(M_PI * 3 / 2);//direction to go 

	circleX = cos(angle) * WANDER_RADIUS;
	circleY = sin(angle) * WANDER_RADIUS;

	nextPos.x = tc->position.x + circleX;
	nextPos.y = tc->position.y + circleY;
	nextPos.w = 10;
	nextPos.h = 10;
	if (Physics::AABB(nextPos, mobArea->getComponent<ColliderComponent>().collider)) {
		goalX = tc->position.x + circleX;
		goalY = tc->position.y + circleY;
	} else {
		goalX = tc->position.x;
		goalY = tc->position.y;
	}
	//check if goalX goalY
}

void Enemy::face() {
	/*TransformComponent * tc = &this->getComponent<TransformComponent>();
	float deltaX = goalX - tc->position.x;
	float deltaY = goalY - tc->position.y;

	//The angle in radians
	tc->angle = atan2(deltaY, deltaX);*/
}

void Enemy::play(const char* animName) {

	//frames = animations[animName].frames;
	//animIndex = animations[animName].index;
	//animSpeed = animations[animName].speed;

}

void Enemy::checkCollision() {

	TransformComponent *  tc = &this->getComponent<TransformComponent>();

	//Enemy hits a wall
	if (Physics::collidesWithWall(this->getComponent<ColliderComponent>().collider)) {
		tc->velocity.x *= -1;
		tc->velocity.y *= -1;
	}

	//Enemy Hit by bullet
	if (Physics::collidesWithTag(this->getComponent<ColliderComponent>().collider, "Bullet")) {
		killEnemy();
	}

	//Enemy hit player
	if (Physics::collidesWithPlayer(this->getComponent<ColliderComponent>().collider)) {

		TransformComponent *  tc = &this->getComponent<TransformComponent>();
		tc->velocity.x = 0;
		tc->velocity.y = 0;
		hitPlayer();

	}
	else {
		collidingWithPlayer = false;
	}

	move();
}

void Enemy::hitPlayer() {
	/*playerCollideTime = SDL_GetTicks();
	play("Attack");
	collidingWithPlayer = true;*/
}

//Play Enemy death sound
//Play death animation
//Declare enemy as dead
void Enemy::killEnemy() {
	Game::mixer->playRandomSound(AudioMixer::skeletonDeathSounds);
	animator->playAnimation("death");
	isDead = true;
	timeOfDeath = SDL_GetTicks();
	/*play("Explode");
	diedAtTime = SDL_GetTicks();
	isDead = true;*/
}

void Enemy::attack(Player* p) {
	if (SDL_GetTicks() > lastAttack + attackDelay) {

		p->damagePlayer(damage);

		lastAttack = SDL_GetTicks();
	}
}

void Enemy::takeDamage(int dmg) {
	this->getComponent<HealthComponent>().damageHealth(dmg);

	if (this->getComponent<HealthComponent>().getHealth() <= 0) {
		killEnemy();
	}
}

void Enemy::respawn() {
	if (SDL_GetTicks() > respawnTime + timeOfDeath) {
		animator->playAnimation("walkDown");
		setPosition(static_cast<float>(rp.getX()), static_cast<float>(rp.getY()));
		this->getComponent<HealthComponent>().resetHealth();
		isDead = false;
	}
}