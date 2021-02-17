#include "time.h"

#include <ce_rendering.h>

float ce::Time::getTime() {
	return SDL_GetTicks() / 1000.0f;
}
ce::Time::Time()
	: m_last(getTime()), m_now(0), m_dt(0), m_fps(0) {}

ce::Time::~Time() {}

void ce::Time::update() {
	m_now = getTime();
	m_dt = m_now - m_last;
	m_fps = 1 / m_dt;
	m_last = m_now;
}