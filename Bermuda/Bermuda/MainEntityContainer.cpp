#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer(void)
{
	m_container[ContainerType::Drawable] = new DrawableContainer();
	m_container[ContainerType::Collidable] = new CollidableContainer();
}

DrawableContainer* MainEntityContainer::getDrawableContainer() {
	return static_cast<DrawableContainer*>(m_container[ContainerType::Drawable]);
}

CollidableContainer* MainEntityContainer::getCollidableContainer() {
	return static_cast<CollidableContainer*>(m_container[ContainerType::Collidable]);
}

MainEntityContainer::~MainEntityContainer(void)
{
}
