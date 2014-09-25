#include "Player.h"


Player::Player(int id)
	: Entity(id)
{
	this->moveSpeed = id;
}

void Player::move() {

}

Player::~Player(void)
{
}
