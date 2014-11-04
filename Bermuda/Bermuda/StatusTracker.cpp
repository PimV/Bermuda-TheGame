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
	achievements.push_back(new Achievement("treesCut"));
	achievements.push_back(new Achievement("rocksMined"));
	achievements.push_back(new Achievement("carrotsPicked"));
	achievements.push_back(new Achievement("applesPicked"));
	treeCut();
}

void StatusTracker::treeCut()
{
	std::cout << "add treeCut amount" << std::endl;
	achievements[TREECUT]->addAmount();
}

void StatusTracker::rockMined()
{
	std::cout << "add rockMined amount" << std::endl;
	achievements[ROCKMINED]->addAmount();
}

void StatusTracker::carrotPicked()
{
	std::cout << "add carrotPicked amount" << std::endl;
	achievements[CARROTPICKED]->addAmount();
}

void StatusTracker::applePicked()
{
	std::cout << "add applePicked amount" << std::endl;
	achievements[APPLEPICKED]->addAmount();
}

void StatusTracker::cleanup()
{
	for (int i = 0; i < achievements.size(); i++)
	{
		delete achievements[i];
	}
	achievements.clear();
}

StatusTracker::~StatusTracker()
{
	cleanup();
}
