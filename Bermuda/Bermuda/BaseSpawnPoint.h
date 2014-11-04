#pragma once
class BaseSpawnPoint
{
private:
	void init(int);

public:
	BaseSpawnPoint(int type);
	virtual ~BaseSpawnPoint();
};

