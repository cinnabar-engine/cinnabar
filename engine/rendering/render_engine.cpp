#include "rendering_engine.h"
#include <core/tpnt_log.h>

void ce::RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ce::RenderEngine::render(unsigned count) {
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void ce::RenderEngine::bind(RenderCommand command) {
	// Update Shader Values TODO: shouldn't this be somewhere else instead of the bind command?
	command.material->update();

	// TODO: get rid of unneccecary binding
	command.mesh->sendToShader(command.material->getShader());
	command.transform->sendToShader(command.material->getShader());
	command.material->getShader()->setMat4("transform.proj", getProjection());
	m_camera->sendToShader(command.material->getShader());

	// Bind Things
	command.mesh->bind();
	command.material->bind();
}

void ce::RenderEngine::unbind(RenderCommand command) {
	command.mesh->unbind();
	command.material->unbind();
}

ce::RenderEngine::RenderEngine()
	: m_aspectRatio(0),
	  m_fov(0),
	  m_near(0),
	  m_far(0),
	  m_camera(NULL) {
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

ce::RenderEngine::~RenderEngine() {}

void ce::RenderEngine::setClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void ce::RenderEngine::setSize(glm::vec2 size) {
	glViewport(0, 0, size.x, size.y);
	m_aspectRatio = size.x / size.y;
}

glm::mat4 ce::RenderEngine::getProjection() {
	return glm::perspective(m_fov, m_aspectRatio, m_near, m_far);
}

void ce::RenderEngine::render() {
	clear();
	for (int i = 0; i < m_commands.size(); i++) {
		RenderCommand command = m_commands[i];
		bind(command);
		render(command.points);
		unbind(command); // TODO: should this go outside the for loop?
	}
	m_commands.clear();
}