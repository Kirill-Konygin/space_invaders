#pragma once
#include "Sprite.h"
//////////////////////////////////////////////////////////////////////////
Sprite::Sprite(Image& image)
{
	initialization(image);
}
Sprite::Sprite(Image&& image)
{
	initialization(image);
}

void Sprite::initialization(Image& image)
{


	float vertices[] = {
		// positions           // texture coords
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, // top right
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f  // top left 
	};


	unsigned int indices[] = {
		0, 1, 3, 
		1, 2, 3  
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &spritePositions);



	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	
	glBindBuffer(GL_ARRAY_BUFFER, spritePositions);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);


	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void Sprite::render()
{

	
	if (m_index == 0)return;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id);


	glBindBuffer(GL_ARRAY_BUFFER, spritePositions);
	glBufferData(GL_ARRAY_BUFFER, m_index * sizeof(glm::mat4), &m_coords[0], GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_coords.size());
	m_index = 0;
}


void Sprite::addMat4(glm::mat4& mat4)
{

	if (m_index < static_cast<int>(m_coords.size()))
	{
		m_coords[m_index] = mat4;
	}
	else
	{
		m_coords.push_back(mat4);
	}
	m_index++;
}

void Sprite::addMat4(glm::mat4&& mat4)
{
	addMat4(mat4);
}




