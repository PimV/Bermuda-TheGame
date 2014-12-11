#pragma once
#include <vector>
#include "Achievement.h"
#include "AchievementsEnum.h"

class StatusTracker
{
public:
	//methodes
	void addAchievementCount(AchievementsEnum enumIn);
	std::vector<Achievement*> getAllAchievements();

	//constructor destructor
	StatusTracker();
	virtual ~StatusTracker();

private:
	//variables
	std::vector<Achievement*> achievements;

	//methodes
	void init();
	void cleanup();
};

