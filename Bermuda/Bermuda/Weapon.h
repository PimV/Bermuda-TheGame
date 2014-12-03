#pragma once
#include "Item.h"
#include "equipable.h"
class Weapon :
	public Equipable
{
public:
	Weapon(void);

	void setAttackDamage(double dmg);
	double getAttackDamage();

	void setAttackRadius(double radius);
	double getAttackRadius();

	void setAttackSpeed(double attackSpeed);
	double getAttackSpeed();

	virtual void use(Player* player);

	virtual ~Weapon(void);

private:
	double attackDamage;
	double attackRadius;
	double attackSpeed
};




