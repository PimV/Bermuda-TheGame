#pragma once
#include "ientitycontainer.h"
#include "DrawableEntity.h"
class DrawableContainer :
	public IEntityContainer
{
public:
	DrawableContainer();


	void add(DrawableEntity* entity);
	std::vector<DrawableEntity*> getContainer();

	virtual ~DrawableContainer();
private: 
	std::vector<DrawableEntity*> m_container;
};

