#include "Weapon.h"


Weapon::Weapon()
{
	this->setAttackDamage(1);
	this->setAttackRadius(1);
}

void Weapon::setAttackDamage(double dmg) {
	this->attackDamage = dmg;
}

double Weapon::getAttackDamage() {
	return this->attackDamage;
}

void Weapon::setAttackSpeed(double attackSpeed) {
	this->attackSpeed = attackSpeed;
}

double Weapon::getAttackSpeed() {
	return this->attackSpeed;
}

void Weapon::setAttackRadius(double radius) {
	this->attackRadius = radius;
}

double Weapon::getAttackRadius() {
	return this->attackRadius;
}


Weapon::~Weapon()
{
}
