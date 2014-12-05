#include "MainEntityContainer.h"

MainEntityContainer::MainEntityContainer() : 
	chunkSize(300)
{
	this->m_container[ContainerType::Drawable] = new DrawableContainer();
	this->m_container[ContainerType::Animating] = new DrawableContainer();
	this->m_container[ContainerType::Collidable] = new CollidableContainer();
	this->m_container[ContainerType::Background] = new BackgroundContainer();
	this->m_container[ContainerType::Interactable] = new InteractableContainer();
	this->m_container[ContainerType::Respawnable] = new RespawnContainer();
	this->m_container[ContainerType::Movable] = new MovableContainer();
	this->m_container[ContainerType::Spawnpoint] = new SpawnpointContainer();
	this->m_container[ContainerType::Destroyed] = new DestroyContainer();
	this->m_container[ContainerType::Light] = new LightContainer();
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
	int chunksY = floor(mapHeight / chunkSize) + 1;
	int chunksX = floor(mapWidth / chunkSize) + 1;

	//Init all containers with chunks
	this->m_container[ContainerType::Collidable]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Drawable]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Animating]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Background]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Interactable]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Movable]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Spawnpoint]->initChunks(chunksY, chunksX);
	this->m_container[ContainerType::Light]->initChunks(chunksY, chunksX);
}

MainEntityContainer::~MainEntityContainer()
{
	this->m_container[ContainerType::Drawable]->cleanup();
	this->m_container[ContainerType::Animating]->cleanup();
	this->m_container[ContainerType::Collidable]->cleanup();
	this->m_container[ContainerType::Background]->cleanup();
	this->m_container[ContainerType::Interactable]->cleanup();
	this->m_container[ContainerType::Respawnable]->cleanup();
	this->m_container[ContainerType::Movable]->cleanup();
	this->m_container[ContainerType::Spawnpoint]->cleanup();
	this->m_container[ContainerType::Destroyed]->cleanup();
	this->m_container[ContainerType::Light]->cleanup();

	delete this->m_container[ContainerType::Drawable];
	delete this->m_container[ContainerType::Animating];
	delete this->m_container[ContainerType::Collidable];
	delete this->m_container[ContainerType::Background];
	delete this->m_container[ContainerType::Interactable];
	delete this->m_container[ContainerType::Respawnable];
	delete this->m_container[ContainerType::Movable];
	delete this->m_container[ContainerType::Spawnpoint];
	delete this->m_container[ContainerType::Destroyed];
	delete this->m_container[ContainerType::Light];
}
