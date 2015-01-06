#include "StatusTracker.h"

enum{
	TREECUT,
	ROCKMINED,
	CARROTPICKED,
	APPLEPICKED,

	BATSKILLED,
	RABBITSKILLED,
	SCORPIONSKILLED,
	WASPSKILLED,
	WOLFSKILLED
};

StatusTracker::StatusTracker()
{
	init();
}

void StatusTracker::init()
{
	achievements.push_back(new Achievement("Trees logged"));
	achievements.push_back(new Achievement("Rocks mined"));
	achievements.push_back(new Achievement("Carrots picked"));
	achievements.push_back(new Achievement("Apples picked"));

	achievements.push_back(new Achievement("Bats killed"));
	achievements.push_back(new Achievement("Rabbits killed"));
	achievements.push_back(new Achievement("Scorpions killed"));
	achievements.push_back(new Achievement("Wasps killed"));
	achievements.push_back(new Achievement("Wolfs killed"));
}

std::vector<Achievement*> StatusTracker::getAllAchievements()
{
	return this->achievements;
}

#pragma region Interactable_objects
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
#pragma endregion

#pragma region Interactable_NPC

void StatusTracker::BatsKilled()
{
	achievements[BATSKILLED]->addAmount();
}

void StatusTracker::RabbitsKilled()
{
	achievements[RABBITSKILLED]->addAmount();
}

void StatusTracker::ScorpionsKilled()
{
	achievements[SCORPIONSKILLED]->addAmount();
}

void StatusTracker::WaspsKilled()
{
	achievements[WASPSKILLED]->addAmount();
}

void StatusTracker::WolfsKilled()
{
	achievements[WOLFSKILLED]->addAmount();
}
#pragma endregion

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
