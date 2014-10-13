#include "BackgroundContainer.h"


BackgroundContainer::BackgroundContainer(void)
{
}

void BackgroundContainer::add(DrawableEntity* entity) {
	this->m_container.push_back(entity);
}

std::vector<DrawableEntity*> BackgroundContainer::getContainer() {
	return this->m_container;
}

BackgroundContainer::~BackgroundContainer(void)
{
}
