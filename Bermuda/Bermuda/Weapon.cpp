#include "Weapon.h"


Weapon::Weapon(void)
{
	this->setAttackDamage(1);
	this->setAttackRadius(1);
}

void Weapon::use(Player* player) {

}

void Weapon::setAttackDamage(double dmg) {
	this->attackDamage = dmg;
}

double Weapon::getAttackDamage() {
	return this->attackDamage;
}

void Weapon::setAttackDamage(double attackSpeed) {
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


Weapon::~Weapon(void)
{
}
