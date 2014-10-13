#pragma once
#include "IEntityContainer.h"
#include "DrawableEntity.h"
#include <vector>
class BackgroundContainer :
	public IEntityContainer
{
public:
	BackgroundContainer(void);

	void add(DrawableEntity* entity);
	std::vector<DrawableEntity*> getContainer();

	~BackgroundContainer(void);
private:
	std::vector<DrawableEntity*> m_container;
};

