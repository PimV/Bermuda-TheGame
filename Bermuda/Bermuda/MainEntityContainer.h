#pragma once
#include "ContainerType.h"
#include "IEntityContainer.h"
#include "DrawableEntity.h"
#include <map>
#include <vector>

class MainEntityContainer
{
public:
	MainEntityContainer(void);
	virtual ~MainEntityContainer(void);

	std::vector<DrawableEntity*>* getDrawableContainer();

private: 
	//std::map<ContainerType, std::vector<Entity*>> m_container;
	std::vector<DrawableEntity*> drawableContainer;
};

