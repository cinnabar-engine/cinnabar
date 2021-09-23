#include <cinnabar-render/render_engine.hpp>

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cinnabar-core/tpnt_log.h>

void ce::RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

ce::RenderEngine::RenderEngine(glm::vec4 clearColor) {
	/*GLenum err = glewInit();
	if (GLEW_OK != err) {
		LOG_ERROR("GLEW error: %s", (const char*)glewGetErrorString(err));
	}
	LOG_INFO("GLEW version: %s", (const char*)glewGetString(GLEW_VERSION));*/
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
	glfwTerminate();
}

void ce::RenderEngine::setClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void ce::RenderEngine::setSize(glm::vec2 size) {
	glViewport(0, 0, size.x, size.y);
}
void ce::RenderEngine::render(Mesh* mesh, Material* material, Transform* transform, Camera* camera) {
	bind(mesh, material, transform, camera);
	glDrawElements(mesh->format, (GLsizei)mesh->GetIndexCount(), GL_UNSIGNED_INT, NULL);
	mesh->unbind(); // TODO: is unbinding needed, and does it reduce performance?
	material->unbind();
}
