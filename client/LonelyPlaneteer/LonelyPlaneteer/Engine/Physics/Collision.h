#pragma once

enum CollisionType : std::size_t {
	player_wall,
	player_enemy,
	movement_mine,
	mine_player,
	fireball_player,
	fireball_enemy,
	fireball_wall,
	movement_wall,
	sword_player,
	sword_enemy
};

struct Collision {
	std::unique_ptr<Entity>& other;
	CollisionType type;
};
