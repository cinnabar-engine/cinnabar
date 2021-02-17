#include "rendering_engine.h"
#include <core/tpnt_log.h>

void ce::RenderingEngine::clear()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ce::RenderingEngine::render(unsigned count)
{
	glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,0);
}

void ce::RenderingEngine::bind(RenderCommand command)
{
	command.material->bind();
	command.mesh->bind();
}

void ce::RenderingEngine::unbind(RenderCommand command)
{
	command.mesh->unbind();
	command.material->unbind();
}

ce::RenderingEngine::RenderingEngine()
:m_aspectRatio(0),
m_fov(0)
{
	/*
	 * GLEW
	 */
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		LOG_ERROR((const char*)glewGetErrorString(err));
	}
	LOG_INFO("Status: Using GLEW " + (const char*)glewGetString(GLEW_VERSION));

	// OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	setClearColor(glm::vec4());
}

ce::RenderingEngine::~RenderingEngine()
{
}

void ce::RenderingEngine::setClearColor(glm::vec4 color)
{
	glClearColor(color.r,color.g,color.b,color.a);
}

void ce::RenderingEngine::setSize(glm::vec2 size)
{
	glViewport(0, 0, size.x, size.y);
	m_aspectRatio = size.x/size.y;
}

glm::mat4 ce::RenderingEngine::getProjection()
{
	return glm::perspective(m_fov,m_aspectRatio, 0.1f, 100.0f);
}



void ce::RenderingEngine::render()
{
	
	clear();
	for(int i=0;i<m_commands.size();i++) {
		RenderCommand command = m_commands[i];
		bind(command);
		render(command.points);
		unbind(command);
	}
	m_commands.clear();
}

