#pragma once

#include <glm/glm.hpp>

namespace ce {
	/**
	 * @brief Represents an offscreen frame buffer
	 * 
	 */
	class Framebuffer {
	 public:
		Framebuffer(bool renderBuffer);
		~Framebuffer();

		void bind(),

		/**
		 * @brief Bind the default frame buffer
		 * 
		 */
			unbind();

		void attachColor(GLuint& p_texture,GLsizei p_width, GLsizei p_height);
		void attachDepth();
		void attachStencil();
		void attachDepthStencil();

		bool isComplete();

	 private:
		glm::uint32 m_FBO;
		glm::uint32 m_RBO;
	};
}
