#pragma once
#include <vector>
#include "Achievement.h"

class StatusTracker
{
public:
	//methodes
	void treeCut();
	void rockMined();
	void carrotPicked();
	void applePicked();
	std::vector<Achievement*> getAllAchievements();
	void setAllStats(std::vector<int> stats);

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

