#include "InputHandler.h"

void InputHandler::HandelInput()
{
	glfwPollEvents();

	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		moveRight();
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		moveLeft();
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		attack();
}

void InputHandler::moveRight()
{
	m_playerCommands.movigEvents.push_back(MovigEvent(glm::vec2(1.f, 0.f)));
}
void InputHandler::moveLeft()
{
	m_playerCommands.movigEvents.push_back(MovigEvent(glm::vec2(-1.f, 0.f)));
}
void InputHandler::attack()
{
	m_playerCommands.Attack = true;
}