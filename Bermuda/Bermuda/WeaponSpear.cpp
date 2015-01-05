#include "WeaponSpear.h"
#include "Items.h"
#include <iostream>
class Player;

WeaponSpear::WeaponSpear(Image* image)
{
	this->setImage(image);
	this->init();
}

void WeaponSpear::init() {
	this->setId((int)Items::Spear);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Weapon);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);

	this->setAttackDamage(10);
	this->setAttackRadius(10);

	this->AnimationType = AnimationEnumType::AttackSpear;
	this->setMaxDurability(100);
	this->setDurability(100);
}

WeaponSpear::~WeaponSpear()
{
}
