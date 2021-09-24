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
		typedef enum {
			DEPTH_NEVER = GL_NEVER,
			DEPTH_LESS = GL_LESS,
			DEPTH_EQUAL = GL_EQUAL,
			DEPTH_LEQUAL = GL_LEQUAL,
			DEPTH_GREATER = GL_GREATER,
			DEPTH_NOTEQUAL = GL_NOTEQUAL,
			DEPTH_GEQUAL = GL_GEQUAL,
			DEPTH_ALWAYS = GL_ALWAYS,
		} DepthFunc;
	 
		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setSize(glm::vec2 size);

		void setRenderOption(GLenum option, bool enable); // TODO: create enum for option

		void setClearColor(glm::vec4 color);
		void setClearDepth(glm::float32 depth);
		void setClearStencil(glm::int32 stencil);

		void setDepthFunc(DepthFunc func);

		void
			clear(BufferBit buffer = DEPTH_BUFFER_BIT),
			render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);

	 private:
		void bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
