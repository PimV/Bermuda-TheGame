#pragma once
#include "Item.h"
#include "equipable.h"
#include "AnimationEnum.h"
class Weapon :
	public Equipable
{
public:
	Weapon();

	void setAttackDamage(double dmg);
	double getAttackDamage();

	void setAttackRadius(double radius);
	double getAttackRadius();

	void setAttackSpeed(double attackSpeed);
	double getAttackSpeed();

	AnimationEnumType getAnimationEnumType();	
	
	virtual ~Weapon();

protected:
	AnimationEnumType AnimationType;

private:
	double attackDamage;
	double attackRadius;
	double attackSpeed;

};
