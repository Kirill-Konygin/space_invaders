#include "Player.h"

Player::Player(Commands& commands, const Configuration& config) :m_commands(commands)
{
	m_worldRightBorder =  config.width / 2.f;
	m_worldLeftBorder  = -config.width / 2.f;	
}

void Player::set(Sprite& sprite, glm::vec2 position)
{
	GameObject gameObject;

	GraphicsComponent graphic;
	graphic.addSprite(sprite);
	gameObject.setGraphicComponent(std::move(graphic));

	CollisionShape collisionShape;
	collisionShape.aabb.max = glm::vec2(0.5f, 0.5f);
	collisionShape.aabb.min = glm::vec2(-0.5f, -0.5f);

	gameObject.setCollisonShape(std::move(collisionShape));
	gameObject.setPosition(std::move(position));
	
	gameObject.setID(0);
	m_gameObjectsCollection.addGameObject(std::move(gameObject));	
}

void Player::setProjectile(Projectiles *proj)
{
	m_projectile = proj;
}

void Player::update(double deltaTime)
{
	m_accumulator += deltaTime;

	for (auto& p : m_commands.movigEvents)
	{
		if (
			((m_gameObjectsCollection.getPosition(0) + p.getDirection()).x < m_worldRightBorder)
			&&
			((m_gameObjectsCollection.getPosition(0) + p.getDirection()).x > m_worldLeftBorder)
			)
		{
			m_gameObjectsCollection.getPositions()[0] += p.getDirection()*static_cast<float>(deltaTime)*10.f;
			m_gameObjectsCollection.getGraphicsComponents()[0].setPos(m_gameObjectsCollection.getPositions()[0]);
		}

	}



	if (m_commands.Attack && !m_fire)
	{
		m_projectile->addProjectile(glm::vec2(m_gameObjectsCollection.getPosition(0)) + glm::vec2(0.f, 1.f));
		m_fire = true;
	}

	if (!m_commands.Attack)
	{
		m_fire = false;
	}

	m_commands.Attack = false;
	m_commands.movigEvents.clear();

}

void Player::render()
{
	m_gameObjectsCollection.getGraphicsComponent(0).render();
}



void Player::processCollision()
{
	for (auto& elem : m_collisions)
	{
		m_lifeCount--;
	}
	m_collisions.clear();
}

int Player::getLifes()
{
	return m_lifeCount;
}

void Player::setLifeCount(int count)
{
	m_lifeCount = count;
}