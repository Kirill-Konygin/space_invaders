#pragma once
#include "Image.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include "Shader.h"
#include <vector>

class Sprite
{
public:	
	
	Sprite(Image& image);
	Sprite(Image&& image);
	void render();
	void addMat4(glm::mat4& mat4);
	void addMat4(glm::mat4&& mat4);		

private:

	void initialization(Image& image);	

	int m_index=0;

	unsigned int VBO, VAO, EBO, spritePositions;
	unsigned int texture_id;
	
	std::vector<glm::mat4> m_coords;

};
