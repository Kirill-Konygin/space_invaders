#pragma once
#include "Projectiles.h"

Projectiles::Projectiles(const Configuration& config, glm::vec2 dir) :m_movingDirection(dir), m_nextID(0)
{
    m_maxID = 100;   

	m_worldBottomBorder= -config.height / 2.f;
	m_worldTopBorder = config.height / 2.f;
}

void Projectiles::setSprite(Sprite& sprite)
{
	m_sprite = &sprite;
}

void Projectiles::move(double deltaTime)
{

	for(unsigned int i=0;i< m_gameObjectsCollection.size();i++)
	{
		m_gameObjectsCollection.getPositions()[i] += m_movingDirection * static_cast<float>(deltaTime) * 20.f;
		m_gameObjectsCollection.getGraphicsComponents()[i].setPos(m_gameObjectsCollection.getPositions()[i]);
	}
}

void Projectiles::render()
{
	for (auto& proj : m_gameObjectsCollection.getGraphicsComponents())
	{
		proj.render();
	}
}

void Projectiles::update(double deltaTime)
{

	move(deltaTime);
	for (unsigned int i = 0; i < m_gameObjectsCollection.size(); i++)
	{
		if (m_gameObjectsCollection.getPositions()[i].y <= m_worldBottomBorder || m_gameObjectsCollection.getPositions()[i].y >= m_worldTopBorder)
		{			
			remove(m_gameObjectsCollection.getIDs()[i]);
		}
	}

}

void Projectiles::remove(int id)
{
	if(m_gameObjectsCollection.containsID(id))m_gameObjectsCollection.remove(id);
}

void Projectiles::addProjectile(glm::vec2 position)
{
	GameObject gameObject;


	GraphicsComponent graphic;
	graphic.addSprite(*m_sprite);	
	gameObject.setGraphicComponent(std::move(graphic));	


	CollisionShape collisionShape;
	collisionShape.aabb.max = glm::vec2(0.1f, 0.5f);
	collisionShape.aabb.min = glm::vec2(-0.1f, -0.5f);
	gameObject.setCollisonShape(std::move(collisionShape));


	gameObject.setPosition(std::move(position));
	

	gameObject.setID(m_nextID);
	gameObject.getGraphicsComponent().setSize(glm::vec2(0.2f, 1.f));

	m_gameObjectsCollection.addGameObject(std::move(gameObject));

	m_nextID++;
	m_nextID %= m_maxID;
	
}


std::vector<CollisionShape> Projectiles::getCollisonShape()
{
	std::vector<CollisionShape> vec;
	for (auto& elem : m_gameObjectsCollection.getColisionShapes())
	{
		vec.push_back(elem);
	}
	return vec;
}

std::vector<int> Projectiles::getID()
{
	return m_gameObjectsCollection.getIDs();
}

void Projectiles::processCollision()
{
	for(auto& elem : m_collisions)
	{
		remove(elem);
	}
	m_collisions.clear();
}

