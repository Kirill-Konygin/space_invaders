#pragma once
#include <vector>

#include "CollisionSystem.h"
#include "Sprite.h"
#include "EventSystem.h"

#include "GameObjectsGroup.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>


#include "Configuration.h"


class Projectiles : public GameObjectsGroup
{
public:
	Projectiles(const Configuration& config, glm::vec2 dir);


	void addProjectile(glm::vec2 position);	
	void setSprite(Sprite& sprite);	
	
	void render();
	void update(double deltaTime);
	void remove(int id);	
	
	void processCollision();
	std::vector<CollisionShape> getCollisonShape();
	std::vector<int> getID();	
	

private:

	void move(double deltaTime);

	glm::vec2 m_movingDirection;	
	
	int m_nextID;
	int m_maxID;

	

	Sprite* m_sprite;
	
	float m_worldBottomBorder, m_worldTopBorder;
};




