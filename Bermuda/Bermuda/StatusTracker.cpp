#include "StatusTracker.h"
#include <iostream>

enum{
	TREECUT,
	ROCKMINED,
	CARROTPICKED,
	APPLEPICKED
};

StatusTracker::StatusTracker()
{
	init();
}

void StatusTracker::init()
{
	achievements.push_back(new Achievement("Trees cut"));
	achievements.push_back(new Achievement("Rocks mined"));
	achievements.push_back(new Achievement("Carrots picked"));
	achievements.push_back(new Achievement("Apples picked"));
}

std::vector<Achievement*> StatusTracker::getAllAchievements()
{
	return this->achievements;
}

void StatusTracker::treeCut()
{
	achievements[TREECUT]->addAmount();
}

void StatusTracker::rockMined()
{
	achievements[ROCKMINED]->addAmount();
}

void StatusTracker::carrotPicked()
{
	achievements[CARROTPICKED]->addAmount();
}

void StatusTracker::applePicked()
{
	achievements[APPLEPICKED]->addAmount();
}

void StatusTracker::setAllStats(std::vector<int> stats)
{
	if (stats.size() <= this->achievements.size())
	{
		for (size_t i = 0; i < stats.size(); i++)
		{
			this->achievements[i]->setAmount(stats[i]);
		}
	}
}

void StatusTracker::cleanup()
{
	for (size_t i = 0; i < achievements.size(); i++)
	{
		delete achievements[i];
		achievements[i] = nullptr;
	}
	std::vector<Achievement*>().swap(this->achievements); //Clear and shrink vector
}

StatusTracker::~StatusTracker()
{
	this->cleanup();
}
