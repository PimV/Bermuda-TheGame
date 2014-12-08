#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer(void) : 
	chunkSize(300)
{
	m_container[ContainerType::Drawable] = new DrawableContainer();
	m_container[ContainerType::Animating] = new DrawableContainer();
	m_container[ContainerType::Collidable] = new CollidableContainer();
	m_container[ContainerType::Background] = new BackgroundContainer();
	m_container[ContainerType::Interactable] = new InteractableContainer();
	m_container[ContainerType::Respawnable] = new RespawnContainer();
	m_container[ContainerType::Movable] = new MovableContainer();
	m_container[ContainerType::Spawnpoint] = new SpawnpointContainer();
	m_container[ContainerType::Destroyed] = new DestroyContainer();
	m_container[ContainerType::Light] = new LightContainer();
}

DrawableContainer* MainEntityContainer::getDrawableContainer() {
	return static_cast<DrawableContainer*>(m_container[ContainerType::Drawable]);
}

AnimatingContainer* MainEntityContainer::getAnimatingContainer() {
	return static_cast<AnimatingContainer*>(m_container[ContainerType::Animating]);
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

SpawnpointContainer* MainEntityContainer::getSpawnpointContainer() {
	return static_cast<SpawnpointContainer*>(m_container[ContainerType::Spawnpoint]);
}

DestroyContainer* MainEntityContainer::getDestroyContainer() {
	return static_cast<DestroyContainer*>(m_container[ContainerType::Destroyed]);
}

LightContainer* MainEntityContainer::getLightContainer() {
	return static_cast<LightContainer*>(m_container[ContainerType::Light]);
}

int MainEntityContainer::getChunkSize()
{
	return this->chunkSize;
}

void MainEntityContainer::initContainerSizes(int mapHeight, int mapWidth)
{
	int chunksY = static_cast<int>(floor(mapHeight / chunkSize) + 1);
	int chunksX = static_cast<int>( floor(mapWidth / chunkSize) + 1);

	//Init all containers with chunks
	m_container[ContainerType::Collidable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Drawable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Animating]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Background]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Interactable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Movable]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Spawnpoint]->initChunks(chunksY, chunksX);
	m_container[ContainerType::Light]->initChunks(chunksY, chunksX);
}

MainEntityContainer::~MainEntityContainer(void)
{
}
