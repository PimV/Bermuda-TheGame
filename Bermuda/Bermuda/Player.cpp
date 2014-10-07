#include "Player.h"
#include <iostream>

Player::Player(int id, double moveSpeed)
	: Entity(id), IMovable(moveSpeed)
{
	this->moveSpeed = id;
}

void Player::move(EnumDirection direction) {
	EnumDirection e = direction;
	std::cout << "Moving player to direction" << enum_strings[(int)e] << std::endl;
}

Player::~Player(void)
{
}
