#pragma once

#include <glad/glad.h>
#include <string>

class Image
{
public:
	Image(std::string path);

	~Image();

	int getWidth();
	int getHeight();
	int getNrComponents();
	const unsigned char& getImage();
	GLenum getFormat();
	unsigned char* imageData;

private:
	int width, height, nrComponents;

	

	GLenum format;
};