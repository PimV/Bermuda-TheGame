#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer(void)
{
	m_container[ContainerType::Drawable] = new DrawableContainer();
	m_container[ContainerType::Collidable] = new CollidableContainer();
	m_container[ContainerType::Background] = new BackgroundContainer();
	m_container[ContainerType::Interactable] = new InteractableContainer();
	m_container[ContainerType::Respawnable] = new RespawnContainer();
	m_container[ContainerType::Movable] = new MovableContainer();
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

InteractableContainer* MainEntityContainer::getInteractableContainer() {
	return static_cast<InteractableContainer*>(m_container[ContainerType::Interactable]);
}

RespawnContainer* MainEntityContainer::getRespawnContainer() {
	return static_cast<RespawnContainer*>(m_container[ContainerType::Respawnable]);
}

MovableContainer* MainEntityContainer::getMovableContainer() {
	return static_cast<MovableContainer*>(m_container[ContainerType::Movable]);
}

void MainEntityContainer::initContainerSizes(int chunksY, int chunksX)
{
	//Init all containers with chunks
	m_container[ContainerType::Collidable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Drawable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Background]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Interactable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Movable]->initChunks(chunksY, chunksX);
}

MainEntityContainer::~MainEntityContainer(void)
{
}
