#include "StatusTracker.h"

StatusTracker::StatusTracker()
{
	init();
}

void StatusTracker::init()
{
	achievements.push_back(new Achievement("Apples picked"));
	achievements.push_back(new Achievement("Carrots picked"));
	achievements.push_back(new Achievement("Fish caught"));
	achievements.push_back(new Achievement("Gold mined"));
	achievements.push_back(new Achievement("Ice mined"));
	achievements.push_back(new Achievement("Cacti chopped"));
	achievements.push_back(new Achievement("Rocks mined"));
	achievements.push_back(new Achievement("Trees chopped"));

	achievements.push_back(new Achievement("Bats killed"));
	achievements.push_back(new Achievement("Rabbits killed"));
	achievements.push_back(new Achievement("Scorpions killed"));
	achievements.push_back(new Achievement("Wasps killed"));
	achievements.push_back(new Achievement("Wolves killed"));
}

std::vector<Achievement*> StatusTracker::getAllAchievements()
{
	return this->achievements;
}

void StatusTracker::addAchievementCount(AchievementsEnum enumIn)
{
	achievements[(int)enumIn]->addAmount();
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
