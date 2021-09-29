#include <cinnabar-render/render_engine.hpp>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cinnabar-core/tpnt_log.h>

ce::RenderEngine::RenderEngine() {
	if (!glfwInit()) {
		LOG_ERROR("Error intialising GLFW");
		exit(1);
	}
	LOG_SUCCESS("GLFW has been initialized");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
ce::RenderEngine::~RenderEngine() {
	glfwTerminate();
}

void ce::RenderEngine::clear(BufferBit buffer) {
	glClear((GLbitfield)buffer);
}

void ce::RenderEngine::bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera) {
	// Update Shader Values TODO: shouldn't this be somewhere else instead of the bind command?
	material->update();

	// TODO: get rid of unneccecary binding
	mesh->sendToShader(material->shader, true);
	material->shader->setUniform("transform.model", transform->getMatrix());
	camera->sendToShader(material->shader);

	// Bind Things
	mesh->bind();
	material->bind();
}

void ce::RenderEngine::setRenderOption(RenderOption option, bool enable) {
	if (enable)
		glEnable((GLenum)option);
	else
		glDisable((GLenum)option);
}

void ce::RenderEngine::setClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}
void ce::RenderEngine::setClearDepth(GLfloat depth) {
	glClearDepth(depth);
}
void ce::RenderEngine::setClearStencil(GLint stencil) {
	glClearStencil(stencil);
}

void ce::RenderEngine::setDepthFunc(DepthFunc func) {
	glDepthFunc((GLenum)func);
}

void ce::RenderEngine::setFramebufferSize(glm::vec2 size) {
	glViewport(0, 0, size.x, size.y);
}
void ce::RenderEngine::render(Mesh* mesh, Material* material, Transform* transform, Camera* camera) {
	bind(mesh, material, transform, camera);
	glDrawElements((GLenum)mesh->format, (GLsizei)mesh->GetIndexCount(), GL_UNSIGNED_INT, NULL);
	mesh->unbind(); // TODO: is unbinding needed, and does it reduce performance?
	material->unbind();
}

int ce::RenderEngine::errorCheck() {
	int errorCount;
	while (true) {
		GLenum err = glGetError();
		if (err == GL_NO_ERROR)
			break;
		else {
			LOG_ERROR("Uncaught GL error: 0x%04x", err);
			errorCount++;
		}
	}
	return errorCount;
}