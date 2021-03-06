#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include <filesystem>
class TextDrawer
{
public:
	TextDrawer(unsigned int SCR_WIDTH,unsigned int  SCR_HEIGHT):shader(std::experimental::filesystem::path("../shaders/VS/text.txt").string().c_str(),
		std::experimental::filesystem::path("../shaders/FS/text.txt").string().c_str())
	{
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			system("pause");
			//return -1;
		}

		FT_Face face;
		if (FT_New_Face(ft, "C:/WINDOWS/FONTS/ARIAL.TTF", 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			system("pause");
			//return -1;
		}

		
		FT_Set_Pixel_Sizes(face, 0, 48);

		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		
		for (unsigned char c = 0; c < 128; c++)
		{
			
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void renderText(std::string text)
	{
		
		shader.use();
		glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

	
		std::string::const_iterator c;
		float shift = 0;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = position.x + ch.Bearing.x * scale+shift;
			float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			glDrawArrays(GL_TRIANGLES, 0, 6);
	
			shift += (ch.Advance >> 6) * scale; 
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void setColor(glm::vec3 color)
	{
		this->color = color;
	}

	void setSize(float size)
	{
		scale = size;
	}

	void setPosition(glm::vec2 pos)
	{
		position = pos;
	}

	void setPosition(float x,float y)
	{
		this->x = x;
		this->y = y;
	}

private:
	struct Character {
		unsigned int TextureID; 
		glm::ivec2   Size;      
		glm::ivec2   Bearing;   
		unsigned int Advance;   
	};

	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO;
	Shader shader;
	glm::vec3 color;
	float scale;
	glm::vec2 position;
	float x, y;
};
