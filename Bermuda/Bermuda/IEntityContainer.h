#pragma once
#include <vector>
class IEntityContainer
{
public:
	IEntityContainer();
	virtual void initChunks(int chunksY, int chunksX);
	virtual void add();
	virtual void remove();
	virtual void cleanup();
	virtual ~IEntityContainer();
};

