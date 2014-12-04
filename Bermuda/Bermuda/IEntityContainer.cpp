#include "IEntityContainer.h"

IEntityContainer::IEntityContainer()
{

}

void IEntityContainer::initChunks(int x, int y)
{

}

void IEntityContainer::add()
{

}

void IEntityContainer::remove()
{

}

void IEntityContainer::cleanup()
{

}

IEntityContainer::~IEntityContainer()
{
	this->cleanup();
}
