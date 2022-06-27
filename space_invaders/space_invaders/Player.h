#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "GameObjectsGroup.h"
#include "EventSystem.h"
#include "Projectiles.h"
#include "Configuration.h"

class Player : public GameObjectsGroup
{
public:		

	Player(Commands& commands,const Configuration& config);
	
	void set(Sprite& sprite, glm::vec2 position);		
	void setProjectile(Projectiles *proj);
	void update(double deltaTime);
	void render();
	
	void setLifeCount(int count);
	
	void processCollision();	
	int getLifes();
	

private:	

		
	float m_worldRightBorder, m_worldLeftBorder;

	Projectiles* m_projectile;
	double m_accumulator=0;
	bool m_fire = false;
	Commands& m_commands;
	int m_lifeCount = 3;
};

