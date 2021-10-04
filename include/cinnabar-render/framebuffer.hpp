#pragma once

#include <glm/glm.hpp>

namespace ce {
	class Framebuffer {
	 public:
		Framebuffer();
		~Framebuffer();

		void bind(), unbind();

	 private:
		glm::uint32 m_FBO;
	};
}
