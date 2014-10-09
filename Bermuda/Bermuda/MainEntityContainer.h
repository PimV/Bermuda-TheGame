#pragma once
#include "ContainerType.h"
#include "IEntityContainer.h"
#include "DrawableContainer.h"
#include "CollidableContainer.h"
#include <map>

class MainEntityContainer
{
public:
	MainEntityContainer();
	DrawableContainer* getDrawableContainer();
	CollidableContainer* getCollidableContainer();
	virtual ~MainEntityContainer();


private: 
	std::map<ContainerType, IEntityContainer*> m_container;
};

