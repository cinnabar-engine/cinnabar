#include <cinnabar-render/render_engine.hpp>

#include <GL/glew.h>

#include <cinnabar-core/tpnt_log.h>

const ce::RenderEngine::BufferBit
	ce::RenderEngine::COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
	ce::RenderEngine::DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
	ce::RenderEngine::STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT;

const ce::RenderEngine::DepthFunc
	ce::RenderEngine::DEPTH_NEVER = GL_NEVER,
	ce::RenderEngine::DEPTH_LESS = GL_LESS,
	ce::RenderEngine::DEPTH_EQUAL = GL_EQUAL,
	ce::RenderEngine::DEPTH_LEQUAL = GL_LEQUAL,
	ce::RenderEngine::DEPTH_GREATER = GL_GREATER,
	ce::RenderEngine::DEPTH_NOTEQUAL = GL_NOTEQUAL,
	ce::RenderEngine::DEPTH_GEQUAL = GL_GEQUAL,
	ce::RenderEngine::DEPTH_ALWAYS = GL_ALWAYS;

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

ce::RenderEngine::RenderEngine(glm::vec4 clearColor) {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		LOG_ERROR("GLEW error: %s", (const char*)glewGetErrorString(err));
	}
	LOG_INFO("GLEW version: %s", (const char*)glewGetString(GLEW_VERSION));
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

void ce::RenderEngine::setSize(glm::vec2 size) {
	glViewport(0, 0, size.x, size.y);
}
void ce::RenderEngine::render(Mesh* mesh, Material* material, Transform* transform, Camera* camera) {
	bind(mesh, material, transform, camera);
	glDrawElements(mesh->format, (GLsizei)mesh->GetIndexCount(), GL_UNSIGNED_INT, NULL);
	mesh->unbind(); // TODO: is unbinding needed, and does it reduce performance?
	material->unbind();
}
