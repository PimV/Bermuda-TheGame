#pragma once
#include "ContainerType.h"
#include "IEntityContainer.h"
#include <map>

class MainEntityContainer
{
public:
	MainEntityContainer(void);
	virtual ~MainEntityContainer(void);
private: 
	std::map<ContainerType, IEntityContainer> m_container;
};

