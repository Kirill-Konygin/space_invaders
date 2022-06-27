#pragma once

#include <GLFW/glfw3.h>
#include "EventSystem.h"

class InputHandler
{
public:
	InputHandler(GLFWwindow* window, Commands& commands) :m_window(window), m_playerCommands(commands){}

	void HandelInput();	

private:

	void moveRight();	
	void moveLeft();	
	void attack();

	GLFWwindow* m_window;
	Commands& m_playerCommands;
	
};