#pragma once

#include <vector>

#include <cinnabar-core/transform.hpp>

#include <cinnabar-render/camera.hpp>
#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>
#include <cinnabar-render/window.hpp>

namespace ce {
	class RenderEngine {
	 public:
		typedef enum {
			COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
			DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
			STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT,
		} BufferBit;
	 
		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setFramebufferSize(glm::vec2 size);

		void setRenderOption(GLenum option, bool enable);

		void setClearColor(glm::vec4 color);
		void setClearDepth(GLfloat depth);
		void setClearStencil(GLint stencil);

		void setDepthFunc(GLenum func);

		void
			clear(GLbitfield buffer = DEPTH_BUFFER_BIT),
			render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);

	 private:
		void bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
