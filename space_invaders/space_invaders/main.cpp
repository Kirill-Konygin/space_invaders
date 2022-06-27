#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <map>

#define GLM_FORCE_RADIANS

#include "Sprite.h"
#include "Image.h"
#include "GameWorld.h"
#include "EventSystem.h"
#include "InputHandler.h"
#include "TextDrawer.h"
#include "Configuration.h"




const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	

	Configuration config;
	config.height = 30;
	config.width = 30;
	config.SCR_HEIGHT = SCR_HEIGHT;
	config.SCR_WIDTH = SCR_WIDTH;
	config.invandersCount = 60;
	config.lineLenght = 10;
	
	
	Commands commands;
	InputHandler inputHandler(window, commands);
	GameWorld gameWorld(config,commands);

	TextDrawer drawer(SCR_WIDTH, SCR_HEIGHT);

	drawer.setColor(glm::vec3(1.0, 0.0f, 0.0f));
	drawer.setSize(1.0f);
	drawer.setPosition(glm::vec2(SCR_WIDTH/2.f-100.f, SCR_HEIGHT / 2.f));
	
	
	while (!glfwWindowShouldClose(window))
	{
		
		inputHandler.HandelInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		if (!gameWorld.gameEnd()) {
			gameWorld.update();
			gameWorld.render();
		}
		else
		{
			drawer.renderText("Game over");
		}
		
	
		glfwSwapBuffers(window);		
	}

	

	
	glfwTerminate();
	return 0;
}





