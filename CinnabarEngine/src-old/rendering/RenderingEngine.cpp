#include "RenderingEngine.h"

void ce::RenderingEngine::clear(glm::vec4 color)
{
	glClearColor(color.r,color.g,color.b,color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ce::RenderingEngine::render(unsigned count)
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void ce::RenderingEngine::bind(RenderCommand command)
{
	if (command.material != NULL) command.material->bind();
	if (command.mesh != NULL) command.mesh->bind();
}

void ce::RenderingEngine::unbind(RenderCommand command)
{
	if (command.mesh != NULL) command.mesh->unbind();
	if (command.material != NULL) command.material->unbind();
}

ce::RenderingEngine::RenderingEngine()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

ce::RenderingEngine::~RenderingEngine()
{
}

void ce::RenderingEngine::render()
{
	clear();
	for (size_t i = 0; i < commands.size(); i++)
	{
		RenderCommand command = commands[i];
		bind(command);
		render(command.pointCount);
		unbind(command);
	}
	commands.clear();
}
