#include <cinnabar-render/framebuffer.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

ce::Framebuffer::Framebuffer() {
	glGenFramebuffers(1, (GLuint*)&m_FBO);
}

ce::Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, (GLuint*)&m_FBO);
}

void ce::Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}
void ce::Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
