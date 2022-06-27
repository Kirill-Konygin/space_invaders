#pragma once
#include "GameObject.h"


void GameObject::setPosition(glm::vec2&& pos)
{
	m_position = pos;
	m_graphic.setPos(m_position);
}

glm::vec2 GameObject::getPosition()
{
	return m_position;
}

void GameObject::setGraphicComponent(GraphicsComponent&& graphic)
{
	m_graphic = graphic;
}

void GameObject::setSize(glm::vec2 scale)
{
	m_graphic.setSize(scale);
}

void GameObject::render()
{
	m_graphic.render();
}

CollisionShape& GameObject::getCollisonShape()
{	
	return m_collisionShape;
}

void GameObject::setCollisonShape(CollisionShape&& collisionShape)
{
	m_collisionShape=collisionShape;
}

GraphicsComponent&  GameObject::getGraphicsComponent()
{
	return m_graphic;
}

void GameObject::setID(int id)
{
	m_id = id;
}

int GameObject::getID()
{
	return m_id;
}