#pragma once

#include "GameObjectsCollection.h"
#include <cassert>
void GameObjectsCollection::addGameObject(GameObject&& gameObject)
{

	while (gameObject.getID() >= static_cast<int>(m_locator.size()))
	{
		m_locator.push_back(-1);
	}

	

	if (m_locator[gameObject.getID()] != -1)
	{
		remove(gameObject.getID());
	}

	m_ids.push_back(std::move(gameObject.getID()));
	m_colisionShapes.push_back(std::move(gameObject.getCollisonShape()));
	m_positions.push_back(std::move(gameObject.getPosition()));
	m_graphicsComponents.push_back(std::move(gameObject.getGraphicsComponent()));


	m_graphicsComponents.back().setPos(m_positions.back());
	m_locator[m_ids.back()] = m_ids.size() - 1;

}

void GameObjectsCollection::remove(int id)
{
	assert(containsID(id)&& " wrong id\n");
	

	m_colisionShapes[m_locator[id]] = m_colisionShapes.back();
	m_graphicsComponents[m_locator[id]] = m_graphicsComponents.back();
	m_positions[m_locator[id]] = m_positions.back();
	m_ids[m_locator[id]] = m_ids.back();
	m_locator[m_ids.back()] = m_locator[id];

	m_colisionShapes.pop_back();
	m_graphicsComponents.pop_back();
	m_positions.pop_back();
	m_ids.pop_back();

	m_locator[id] = -1;		
	

	
}

std::vector<CollisionShape>&     GameObjectsCollection::getColisionShapes()
{
	return m_colisionShapes;
}

std::vector<glm::vec2>&         GameObjectsCollection::getPositions()
{
	return m_positions;
}

std::vector<GraphicsComponent>& GameObjectsCollection::getGraphicsComponents()
{
	return m_graphicsComponents;
}

std::vector<int>&               GameObjectsCollection::getIDs()
{
	return m_ids;
}

CollisionShape&                  GameObjectsCollection::getColisionShape(int id)
{
	assert(containsID(id) && " wrong id\n");
	return m_colisionShapes[m_locator[id]];
}

glm::vec2&                      GameObjectsCollection::getPosition(int id)
{	
	assert(containsID(id) && " wrong id\n");
	return m_positions[m_locator[id]];
}

GraphicsComponent&              GameObjectsCollection::getGraphicsComponent(int id)
{
	assert(containsID(id) && " wrong id\n");
	return m_graphicsComponents[m_locator[id]];
}

size_t  GameObjectsCollection::size()
{
	return m_ids.size();
}

bool  GameObjectsCollection::containsID(int id)
{
	return m_locator[id] >= 0;
}