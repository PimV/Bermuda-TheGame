#include "Player.h"


Player::Player(int id, double moveSpeed)
	: Entity(id), IMovable(moveSpeed)
{
	this->moveSpeed = id;
}

void Player::move() {

}

Player::~Player(void)
{
}
