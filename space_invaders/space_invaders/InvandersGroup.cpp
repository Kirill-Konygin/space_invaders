
#include "InvandersGroup.h"

InvandersGroup::InvandersGroup(const Configuration& config) : m_lineLenght(config.lineLenght) 
{
	
	m_worldRightBorder  =   config.width  / 2.f;
	m_worldLeftBorder   =  -config.width  / 2.f;
	m_worldTopBorder    =   config.height / 2.f;
	m_worldBottomBorder =  -config.height / 2.f;
}

int InvandersGroup::getScore()
{
	return m_scoreCounter;
}

void InvandersGroup::setInvanders(std::vector<std::pair<Sprite, Sprite>>& sprite, unsigned int count)
{

	direction = RIGHT;
	float offset = 1.5f;
	float posX = m_worldLeftBorder / offset + 1;
	float posY = m_worldTopBorder / offset - 1;
	int id = 0;
	int iter = 0;
	for (unsigned int i = 0; i < m_lineLenght; i++)
	{
		m_invanders.push_back(std::vector<int>());
	}

	int currentSprite = 0;
	int line = 0;

	for (unsigned int i = 0; i < count; i++)
	{
		GameObject gameObject;

		GraphicsComponent graphic;
		graphic.addSprite(sprite[currentSprite].first);
		graphic.addSprite(sprite[currentSprite].second);

		gameObject.setGraphicComponent(std::move(graphic));
		

		CollisionShape collisionShape;
		collisionShape.aabb.max = glm::vec2(0.5f, 0.5f);
		collisionShape.aabb.min = glm::vec2(-0.5f, -0.5f);

		gameObject.setCollisonShape(std::move(collisionShape));

		
		gameObject.setPosition(glm::vec2(posX*offset, posY*offset));
		gameObject.setID(id);
		m_invanders[iter].push_back(id);
		m_gameObjectsCollection.addGameObject(std::move(gameObject));
		id++;
		posX++;
		iter++;

		if (((i + 1) % m_lineLenght) == 0)
		{
			posX = m_worldLeftBorder / offset + 1;
			posY--;
			iter = 0;
			line++;
			if (line % 2 == 0)currentSprite++;
			if (currentSprite == sprite.size())
			{
				currentSprite = 0;
			}

		}

	}


	m_maxCount = m_gameObjectsCollection.size();
}

void InvandersGroup::render()
{
	for (auto& elem : m_gameObjectsCollection.getGraphicsComponents())
	{
		elem.render();
	}

}

void InvandersGroup::move(MovmentDirections movment)
{
	glm::vec2 offset(0.f, 0.f);
	switch (movment)
	{
	case(RIGHT):
	{
		offset.x += 0.5f;
		break;
	}

	case(LEFT):
	{
		offset.x -= 0.5f;
		break;
	}

	case(DOWN):
	{
		offset.y -= 1.f;
		break;
	}

	case(UP):
	{
		offset.y += 1.f;
		break;
	}
	}

	for (unsigned int i = 0; i < m_gameObjectsCollection.size(); i++)
	{
		m_gameObjectsCollection.getPositions()[i] += offset;
		m_gameObjectsCollection.getGraphicsComponents()[i].setPos(m_gameObjectsCollection.getPositions()[i]);
	}



}
float InvandersGroup::getRightBorder()
{
	float max = m_worldLeftBorder;
	return m_gameObjectsCollection.getPosition(m_invanders.back().front()).x;
	return max;

}
float InvandersGroup::getLeftBorder()
{
	float min = m_worldRightBorder;
	return m_gameObjectsCollection.getPosition(m_invanders.front().front()).x;
	return min;
}

float InvandersGroup::getTopBorder()
{
	float max = m_worldBottomBorder;
	for (auto& invander : m_invanders)
	{
		max = std::max(m_gameObjectsCollection.getPosition(invander.front()).y, max);
	}
	return max;
}
float InvandersGroup::getBottomBorder()
{
	float min = m_worldTopBorder;
	for (auto& invander : m_invanders)
	{
		min = std::min(m_gameObjectsCollection.getPosition(invander.back()).y, min);
	}
	return min;
}

const std::vector<glm::vec2> InvandersGroup::getAttackPositions()
{
	std::vector<glm::vec2> positions;
	for (auto& invander : m_invanders)
	{
		positions.emplace_back(m_gameObjectsCollection.getPosition(invander.back()) + glm::vec2(0.f, -1.5f));
	}

	return positions;
}



void InvandersGroup::update(double deltaTime)
{
	m_accumulator += deltaTime;
	while (m_accumulator >= S_PER_UPDATE * (m_gameObjectsCollection.size() / (double)m_maxCount))
	{
		m_accumulator -= S_PER_UPDATE * (m_gameObjectsCollection.size() / (double)m_maxCount);

		for (auto& elem : m_gameObjectsCollection.getGraphicsComponents())
		{
			elem.switchToNextSprite();
		}

		if ((getRightBorder() + 1.f) >= m_worldRightBorder)
		{
			if (direction == DOWN)
			{
				direction = LEFT;
			}
			else
			{
				direction = DOWN;
			}
		}
		if ((getLeftBorder() - 1.f) <= m_worldLeftBorder)
		{
			if (direction == DOWN)
			{
				direction = RIGHT;
			}
			else
			{
				direction = DOWN;
			}
		}
		move(direction);
		for (auto& elem : getAttackPositions())
		{
			if (std::rand() % 50 + 1 == 1)
			{
				m_projectile->addProjectile(elem);
			}
		}
	}
}


void InvandersGroup::remove(int id)
{
	int column = 0;
	for (unsigned int i = 0; i < m_invanders.size(); i++)
	{
		if (m_invanders[i].front() % m_lineLenght == id % m_lineLenght)
		{
			column = i;
			break;
		}
	}


	for (unsigned int i = 0; i < m_invanders[column].size(); i++)
	{
		if (m_invanders[column][i] == id)
		{
			m_invanders[column].erase(m_invanders[column].begin() + i);
		}
	}

	if (m_invanders[column].size() == 0)
	{
		m_invanders.erase(m_invanders.begin() + column);
	}

	m_gameObjectsCollection.remove(id);	
}

void InvandersGroup::processCollision()
{
	for (auto& elem : m_collisions)
	{
		remove(elem);
		m_scoreCounter++;
	}
	m_collisions.clear();
}

bool InvandersGroup::empty()
{
	return m_gameObjectsCollection.size() == 0;
}

void InvandersGroup::setProjectile(Projectiles* proj)
{
	m_projectile = proj;
}