#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer(void)
{
}

std::vector<DrawableEntity*>* MainEntityContainer::getDrawableContainer()
{
	return &drawableContainer;
}


MainEntityContainer::~MainEntityContainer(void)
{
}
