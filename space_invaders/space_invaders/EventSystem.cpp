#pragma once

#include "EventSystem.h"

glm::vec2 MovigEvent:: getDirection()
{
	return m_dir;
}

MovigEvent::MovigEvent(glm::vec2 dir) :m_dir(dir){}
