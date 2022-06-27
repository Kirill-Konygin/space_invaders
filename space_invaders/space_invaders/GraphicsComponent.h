#pragma once
#include "Sprite.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



class GraphicsComponent
{
public:
	void setPos(glm::vec2& position);
	void setSize(glm::vec2 scale);
	void addSprite(Sprite& sprite);
	void switchToNextSprite();

	void render();
	
private:
	std::vector<std::reference_wrapper<Sprite>> m_sprites;
	glm::mat4 m_positionMatrix;
	glm::mat4 m_scaleMatrix;
	int m_currentSpite = 0;

};
