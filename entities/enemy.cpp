#include "enemy.h"
#include <iostream>
#include "math.h"


Enemy::Enemy(Scene *scene, float x, float y) : Tiger(scene, x, y) {
	std::vector<Entity*> players = scene->get_entities_of_type(1);
	std::cout << players.size() << std::endl;
	player = static_cast<Player*>(players[0]);
}

void Enemy::handle_driving() {

}

void Enemy::handle_turret() {
	std::pair<int, int> player_position = player->get_position();
	float target_angle = atan2(player_position.second - y, player_position.first - x);
	target_angle += M_PI / 2;
	if (target_angle > M_PI) {
		target_angle = -M_PI + target_angle - M_PI;
	}
	if (turret_angle > M_PI) {
		turret_angle = -M_PI + turret_angle - M_PI;
	} else if (turret_angle < -M_PI) {
		turret_angle = M_PI - (turret_angle + M_PI);
	}



	bool direction;
	if (target_angle > turret_angle) {
		if (target_angle - turret_angle > M_PI) {
			direction = false;
		} else {
			direction = true;
		}
	} else {
		if (turret_angle - target_angle > M_PI) {
			direction = true;
		} else {
			direction = false;
		}
	}
	rotate_turret(direction);
}

void Enemy::handle_fire() {

}


void Enemy::update() {
    handle_driving();
    handle_turret();
    handle_fire();
    Tiger::update();
}