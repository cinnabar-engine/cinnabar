#include "Time.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Time::Time()
{
	this->last = this->getTime();
	this->now = 0;
	this->dt = 0;
	this->fps = 0;
}

Time::~Time()
{
}

void Time::update()
{
	this->now = this->getTime();
	this->dt = this->now - this->last;
	this->fps = 1 / this->dt;
	this->last = this->now;
}

float Time::getDeltaTime()
{
	return this->dt;
}

float Time::getFPS()
{
	return this->fps;
}

float Time::getTime()
{
	return glfwGetTime();
}
