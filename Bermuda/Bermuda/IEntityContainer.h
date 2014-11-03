#pragma once
#include <vector>
class IEntityContainer
{
public:
	virtual void initChunks(int chunksY, int chunksX);
	virtual ~IEntityContainer();
};

