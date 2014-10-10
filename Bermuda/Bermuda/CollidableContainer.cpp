#include "CollidableContainer.h"


CollidableContainer::CollidableContainer(void)
{
}

void CollidableContainer::add(Collidable* collidable) {
	this->m_container.push_back(collidable);
}

std::vector<Collidable*> CollidableContainer::getContainer() {
	return this->m_container;
}


CollidableContainer::~CollidableContainer(void)
{
}
