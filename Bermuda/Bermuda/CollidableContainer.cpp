#include "CollidableContainer.h"


CollidableContainer::CollidableContainer(void)
{
}

void CollidableContainer::add(CollidableEntity* collidable) {
	this->m_container.push_back(collidable);
}

std::vector<CollidableEntity*> CollidableContainer::getContainer() {
	return this->m_container;
}


CollidableContainer::~CollidableContainer(void)
{
}
