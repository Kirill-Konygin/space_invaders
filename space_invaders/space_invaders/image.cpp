#include "Image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"



Image::Image(std::string path) :width(0), height(0), nrComponents(0), imageData(nullptr)
{
	
	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load(path.c_str(), &width, &height, &nrComponents,4);
	if (imageData == nullptr)
	{
		std::cerr << "Texture failed to load at path: " << path.c_str() << std::endl;
		exit(2);
	}

	else
	{
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

	}

	
}

Image::~Image()
{
	stbi_image_free(imageData);
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

int Image::getNrComponents()
{
	return nrComponents;
}

const unsigned char& Image::getImage()
{
	return *imageData;
}


GLenum Image::getFormat()
{
	return format;
}