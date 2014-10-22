#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer(void)
{
	m_container[ContainerType::Drawable] = new DrawableContainer();
	m_container[ContainerType::Collidable] = new CollidableContainer();
	m_container[ContainerType::Background] = new BackgroundContainer();
}

DrawableContainer* MainEntityContainer::getDrawableContainer() {
	return static_cast<DrawableContainer*>(m_container[ContainerType::Drawable]);
}

CollidableContainer* MainEntityContainer::getCollidableContainer() {
	return static_cast<CollidableContainer*>(m_container[ContainerType::Collidable]);
}

BackgroundContainer* MainEntityContainer::getBackgroundContainer() {
	return static_cast<BackgroundContainer*>(m_container[ContainerType::Background]);
}

void MainEntityContainer::initContainerSizes(int chunksY, int chunksX)
{
	//Init all containers with chunks
	m_container[ContainerType::Collidable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Drawable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Background]->initChunks(chunksY, chunksX);
}

MainEntityContainer::~MainEntityContainer(void)
{
}
