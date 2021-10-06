#include <cinnabar-render/framebuffer.hpp>

#include <GL/glew.h>
#include <glm/glm.hpp>

ce::Framebuffer::Framebuffer() {
	glGenFramebuffers(1, (GLuint*)&m_FBO);
}

ce::Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, (GLuint*)&m_FBO);
}

/**
 * @brief Bind the frame buffer
 * 
 */
void ce::Framebuffer::bind() {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
}

void ce::Framebuffer::unbind() {
	// I did draw because
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

glm::uint32 createRenderBuffer(GLsizei p_width, GLsizei p_height,GLenum p_internalformat=GL_DEPTH24_STENCIL8) {
	glm::uint32 rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER,rbo);
	glRenderbufferStorage(GL_RENDERBUFFER,p_internalformat,p_width,p_height);
	return rbo;
}

void ce::Framebuffer::attachColor(GLuint& p_texture,GLsizei p_width, GLsizei p_height) {
	//GL_COLOR_ATTACHMENT0
	m_RBO = createRenderBuffer(p_width,p_height);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, p_texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,m_RBO);

}
void ce::Framebuffer::attachDepth() {
}
void ce::Framebuffer::attachStencil() {
}
void ce::Framebuffer::attachDepthStencil() {
}


		bool ce::Framebuffer::isComplete() {
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
		}