#pragma once
#include <vector>
#include "GameObjectsCollection.h"

class GameObjectsGroup
{
public:
	virtual void update(double deltaTime) = 0;
	virtual void processCollision() = 0;
	virtual void render() = 0;

	std::vector<int>& getCollisions();
	GameObjectsCollection& getGameObjects();

protected:

	GameObjectsCollection m_gameObjectsCollection;
	std::vector<int> m_collisions;
	
};

