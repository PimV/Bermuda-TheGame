#include "DrawableContainer.h"


DrawableContainer::DrawableContainer() : IEntityContainer()
{
}

void DrawableContainer::add(DrawableEntity* entity) {
	this->m_container.push_back(entity);
}

std::vector<DrawableEntity*> DrawableContainer::getContainer() {
	return this->m_container;
}


DrawableContainer::~DrawableContainer()
{
}
