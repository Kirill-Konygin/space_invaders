#include "GameObjectsGroup.h"

std::vector<int>& GameObjectsGroup::getCollisions()
{
	return m_collisions;
}

GameObjectsCollection& GameObjectsGroup::getGameObjects()
{
	return m_gameObjectsCollection;
}