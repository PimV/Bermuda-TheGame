#pragma once
#include "ImageLoader.h"
#include "Entity.h"
#include "Objects.h"
#include <map>

class ObjectFactory
{
private:
	static ObjectFactory objectFactory;
	std::map<Objects, int> objectImageIDs;
public:
	ObjectFactory();
	void loadObjectTileSets(ImageLoader* imgLoader);
	Entity* createObject(Objects object, int id, double x, double y);

	virtual ~ObjectFactory();
	static ObjectFactory* Instance() {
		return &objectFactory;
	};
};

