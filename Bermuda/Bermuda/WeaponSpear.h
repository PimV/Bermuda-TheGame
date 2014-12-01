#pragma once
#include "weapon.h"
enum class Items;

class WeaponSpear :
	public Weapon
{
public:
	WeaponSpear(Image* image);
	void init();
	void use(Player* player);
	virtual ~WeaponSpear(void);
};

