#include <cinnabar-core/time.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

ce::Time::Time()
	: m_dt(0), m_fps(0) {
	update(false, false);
}

ce::Time::~Time() {}

void ce::Time::recalculate(bool dt, bool fps) {
	m_now = glfwGetTime();
	if (dt)
		m_dt = m_now - m_last;
	if (fps)
		m_fps = 1.0 / (m_now - m_last);
}

void ce::Time::update(bool dt, bool fps) {
	recalculate(dt, fps);
	m_last = m_now;
}

void ce::Time::waitUntilDelta(double dt) {
	do
		recalculate(true, false);
	while (m_dt < dt);
}