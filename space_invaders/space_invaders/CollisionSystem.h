#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>

class GameObjectsGroup;

struct AABB
{
	glm::vec2 min, max;
};

struct CollisionShape
{		
	AABB aabb;		
};

struct CollisionObject
{
	CollisionShape collisionShape;
	int id;
	int8_t collisionGroup;
	std::vector<int>* collision;
};

struct EndPoint
{
	float pos;
	int id;
	bool max;	
};



class CollisionSystem
{
public:
	void addGameObjects(GameObjectsGroup& gameObjectGroup, int collisionGroup);
	void calculate();
		
	

private:
	bool collision(AABB a, AABB b);
	std::vector<CollisionObject> m_collisionObjects;
};