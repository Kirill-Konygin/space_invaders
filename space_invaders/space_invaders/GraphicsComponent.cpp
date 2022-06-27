#pragma once
#include "GraphicsComponent.h"

void GraphicsComponent::setPos(glm::vec2& position)
{
	m_positionMatrix = glm::translate(glm::mat4(1.f), glm::vec3(position, 0.f));
}


void GraphicsComponent::addSprite(Sprite& sprite)
{
	m_sprites.push_back(sprite);
}

void GraphicsComponent::render()
{	
	m_sprites[m_currentSpite].get().addMat4(m_positionMatrix*m_scaleMatrix);
}

void GraphicsComponent::setSize(glm::vec2 scale)
{
	m_scaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(scale, 1.f));
}

void GraphicsComponent::switchToNextSprite()
{
	if (++m_currentSpite == m_sprites.size())m_currentSpite = 0;
}