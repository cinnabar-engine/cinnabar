#include "rendering_engine.h"

void ce::RenderingEngine::clear(glm::vec4 color)
{
	glClearColor(color.r,color.g,color.b,color.a);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void ce::RenderingEngine::render(unsigned int count)
{
	glDrawElements(GL_TRIANGLES,count,GL_UNSIGNED_INT,0);
}

void ce::RenderingEngine::bind(ce::RenderCommand command)
{
	if(command.texture!=NULL) command.texture->bind();
	if(command.mesh!=NULL) command.mesh->bind();
	if(command.mesh!=NULL && command.shader!=NULL) command.mesh->sendToShader(command.shader);
	if(command.shader!=NULL) command.shader->bind();
}

void ce::RenderingEngine::unbind(ce::RenderCommand command)
{
	if(command.texture!=NULL) command.texture->unbind();
	if(command.mesh!=NULL) command.mesh->unbind();
	if(command.shader!=NULL) command.shader->unbind();
}


ce::RenderingEngine::RenderingEngine()
{
	//Open GL Setup
	glEnable(GL_DEPTH_TEST);
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
		render(command.point_count);
		unbind(command);
	}
	commands.clear();
}

