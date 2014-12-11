#pragma once
#include "entity.h"

class HealthEntity :
	virtual public Entity
{
private:
	double health;
	double maxHealth;

	bool showBar;
	float timeStartShowBar;

public:
	HealthEntity(int id, double x, double y, double maxHealth);
	virtual ~HealthEntity(void);

	double getHealth();
	double getMaxHealth();

	double getPercentageOfCurrentHealth();

	void decreaseHealth(double health);
	void increaseHealth(double health);

	void setShowBar(bool show);
	bool getShowBar();

	void setTimeStartShowBar(float time);
	float getTimeStartShowBar();
};

