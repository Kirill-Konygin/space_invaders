#pragma once

#include "Sprite.h"
#include "GameObjectsGroup.h"
#include "EventSystem.h"

#include "Projectiles.h"


#include "Configuration.h"


class InvandersGroup : public GameObjectsGroup
{
public:
	InvandersGroup(const Configuration& config);

	void setInvanders(std::vector<std::pair<Sprite, Sprite>>& sprite, unsigned int count = 1);

	
	void remove(int id);
	bool empty();

	const std::vector<glm::vec2> getAttackPositions();


	void update(double deltaTime);
	void render();
	
	void setProjectile(Projectiles* proj);

	float getRightBorder();
	float getLeftBorder();
	float getTopBorder();
	float getBottomBorder();	

	int getScore();
	
	void processCollision();


private:

	enum MovmentDirections
	{
		LEFT, RIGHT, UP, DOWN
	};

	void move(MovmentDirections movment);

	float m_worldRightBorder, m_worldLeftBorder, m_worldTopBorder, m_worldBottomBorder;

	unsigned int m_lineLenght;
	

	std::vector<std::vector<int>> m_invanders;
	
	double m_accumulator=0;
	double S_PER_UPDATE=1.0/2.5;
	MovmentDirections direction=RIGHT;

	

	int m_maxCount = 0;
	int m_scoreCounter = 0;
	
	Projectiles* m_projectile;
};

