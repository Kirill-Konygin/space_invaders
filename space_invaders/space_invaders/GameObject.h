#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>


#include "GraphicsComponent.h"
#include "CollisionSystem.h"


class GameObject
{
public:
	
	void setPosition(glm::vec2&& pos);
	glm::vec2 getPosition();

	void setID(int id);
	int  getID();
	
	void setGraphicComponent(GraphicsComponent&& graphic);
	void setSize(glm::vec2 scale);

	void render();	

	CollisionShape& getCollisonShape();
	void setCollisonShape(CollisionShape&& collisionShape);

	GraphicsComponent& getGraphicsComponent();	

private:
	
	int m_id;
	GraphicsComponent m_graphic;
	glm::vec2 m_position;
	CollisionShape m_collisionShape;
};