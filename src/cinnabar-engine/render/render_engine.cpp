#include "render_engine.h"
#include <GL/glew.h>
#include <core/tpnt_log.h>

void ce::RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ce::RenderEngine::bind(RenderCommand command) {
	// Update Shader Values TODO: shouldn't this be somewhere else instead of the bind command?
	command.material->update();

	// TODO: get rid of unneccecary binding
	// TODO: this stuff should be changed when shaders/materials are less hardcoded
	Shader* shader = command.material->getShader();
	command.mesh->sendToShader(shader, true);
	shader->setUniform("transform.model", command.transform->getMatrix());
	command.camera->sendToShader(shader, m_aspectRatio); // TODO: make aspect ratio need to be sent to camera manually on window resize, remove m_aspectRatio from renderEngine

	// Bind Things
	command.mesh->bind();
	command.material->bind();
}

void ce::RenderEngine::unbind(RenderCommand command) {
	command.mesh->unbind();
	command.material->unbind();
}

ce::RenderEngine::RenderEngine(glm::vec4 clearColor)
	: m_aspectRatio(0) {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		LOG_ERROR((const char*)glewGetErrorString(err));
	}
	LOG_INFO("Status: Using GLEW %s", (const char*)glewGetString(GLEW_VERSION));
	/*if () { // TODO: get GL version
		LOG_ERROR("Wrong GL version %s", );
		SDL_Quit();
		exit(1);
	}*/

	// OpenGL Setup
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setClearColor(clearColor);
}
ce::RenderEngine::~RenderEngine() {
	SDL_Quit();
}

void ce::RenderEngine::setClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void ce::RenderEngine::setSize(glm::vec2 size) {
	glViewport(0, 0, size.x, size.y);
	m_aspectRatio = size.x / size.y;
}
void ce::RenderEngine::render() {
	clear();
	for (RenderCommand command : m_commands) {
		bind(command);
		glDrawElements(GL_TRIANGLES, (GLsizei)command.mesh->GetIndexCount(), GL_UNSIGNED_INT, NULL);
		unbind(command); // TODO: should this go outside the for loop?
	}
	m_commands.clear();
}
