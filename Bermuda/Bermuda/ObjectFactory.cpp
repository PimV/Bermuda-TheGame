#include "ObjectFactory.h"
#include "PlayState.h"
#include "Campfire.h"

ObjectFactory ObjectFactory::objectFactory;

ObjectFactory::ObjectFactory()
{
}

void ObjectFactory::loadObjectTileSets(ImageLoader* imgLoader)
{
	objectImageIDs[Objects::Campfire] = imgLoader->loadTileset("Objects\\Campfire 50x52.png", 50, 52);
}

Entity* ObjectFactory::createObject(Objects object, int id, double x, double y)
{
	int chunkSize = PlayState::Instance()->getMainEntityContainer()->getChunkSize();
	switch (object)
	{
	case Objects::Campfire:
		return new Campfire(id, x, y, objectImageIDs[Objects::Campfire]);
		break;
	default:
		return nullptr;
		break;
	}
}

ObjectFactory::~ObjectFactory()
{
}
