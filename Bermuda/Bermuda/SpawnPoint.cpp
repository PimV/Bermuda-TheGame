#include "Spawnpoint.h"


Spawnpoint::Spawnpoint(int type, double x, double y, int chunkSize) 
: Entity(type, x, y, chunkSize), BaseSpawnPoint(type)
{
}



Spawnpoint::~Spawnpoint()
{
}
