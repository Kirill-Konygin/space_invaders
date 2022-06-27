#pragma once
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>


class MovigEvent
{
public:
	MovigEvent(glm::vec2 dir);	
	glm::vec2 getDirection();
	

private:
	glm::vec2 m_dir;
};

struct Commands
{
	std::vector<MovigEvent>  movigEvents;
	bool Attack = false;
};

