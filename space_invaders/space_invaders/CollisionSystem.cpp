#pragma once
#include <iostream>
#include "CollisionSystem.h"
#include "Projectiles.h"
#include "GameObjectsGroup.h"
#include <set>

void CollisionSystem::addGameObjects(GameObjectsGroup& gameObjectGroup, int collisionGroup)
{
	GameObjectsCollection& gameObjectsCollection = gameObjectGroup.getGameObjects();
	for(unsigned int i=0;i< gameObjectsCollection.size();i++)
	{
		CollisionObject collisionObject;
		collisionObject.collisionShape.aabb.max = gameObjectsCollection.getColisionShapes()[i].aabb.max+ gameObjectsCollection.getPositions()[i];
		collisionObject.collisionShape.aabb.min = gameObjectsCollection.getColisionShapes()[i].aabb.min + gameObjectsCollection.getPositions()[i];
		collisionObject.collision = &gameObjectGroup.getCollisions();
		collisionObject.id = gameObjectsCollection.getIDs()[i];
		collisionObject.collisionGroup = collisionGroup;
			
		m_collisionObjects.push_back(collisionObject);
	}
	
}


void CollisionSystem::calculate()
{
	int iter = 0;
	std::vector<EndPoint> endPoints;
	for(auto & elem : m_collisionObjects)
	{				
		EndPoint endPoint1;
		EndPoint endPoint2;

		endPoint1.id = iter;
		endPoint2.id = iter;

		endPoint1.max = true;
		endPoint2.max = false;

		endPoint1.pos = elem.collisionShape.aabb.max.x;
		endPoint2.pos = elem.collisionShape.aabb.min.x;

		endPoints.push_back(std::move(endPoint1));
		endPoints.push_back(std::move(endPoint2));

		iter++;
	}

	std::qsort(
		endPoints.data(),
		endPoints.size(),
		sizeof(decltype(endPoints)::value_type),
		[](const void* x, const void* y) {
		const EndPoint arg1 = *static_cast<const EndPoint*>(x);
		const EndPoint arg2 = *static_cast<const EndPoint*>(y);		
		if (arg1.pos < arg2.pos) return -1;
		if (arg1.pos > arg2.pos) return 1;
		return 0;
	});

	std::set<int> activePoints;
	std::vector <std::pair<int, int>> collisionPairs;

	for(auto& point: endPoints)
	{
		
		if(point.max)
		{
			activePoints.erase(point.id);
		}
		else
		{			
			
			for (auto& elem : activePoints)
			{
				collisionPairs.push_back(std::pair<int, int>(point.id, elem));
			}
			activePoints.insert(point.id);		
			
		}
	}



	for(auto& elem:collisionPairs)
	{
		if(m_collisionObjects[elem.first].collisionGroup != m_collisionObjects[elem.second].collisionGroup)
		{
			if (collision(m_collisionObjects[elem.first].collisionShape.aabb, m_collisionObjects[elem.second].collisionShape.aabb))
			{
				//TODO narrow phase collision detection
				m_collisionObjects[elem.first].collision->push_back(m_collisionObjects[elem.first].id);
				m_collisionObjects[elem.second].collision->push_back(m_collisionObjects[elem.second].id);
			}
		}
	
		
	}
	
	m_collisionObjects.clear();
}




bool CollisionSystem::collision(AABB a, AABB b)
{
	return !(a.min.x > b.max.x ||
			 a.max.x < b.min.x ||
			 a.min.y > b.max.y ||
			 a.max.y < b.min.y);
}
