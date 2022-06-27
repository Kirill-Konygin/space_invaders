#pragma once
#include "GameObject.h"
#include <vector>
#include <cassert>

class GameObjectsCollection
{
public:
	void addGameObject(GameObject&& gameObject);
	void remove(int id);

	bool containsID(int id);	

	std::vector<CollisionShape>&     getColisionShapes();
	std::vector<glm::vec2>&          getPositions();
	std::vector<GraphicsComponent>&  getGraphicsComponents();
	std::vector<int>&                getIDs();

	CollisionShape&                  getColisionShape(int id);
	glm::vec2&                       getPosition(int id);
	GraphicsComponent&               getGraphicsComponent(int id);

	size_t size();
	
private:
	std::vector<int> m_locator;

	std::vector<int> m_ids;
	std::vector<CollisionShape> m_colisionShapes;
	std::vector<glm::vec2> m_positions;
	std::vector<GraphicsComponent> m_graphicsComponents;
};


