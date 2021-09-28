#pragma once

#include <vector>

#include <cinnabar-core/transform.hpp>

#include <cinnabar-render/types.hpp>
#include <cinnabar-render/camera.hpp>
#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>
#include <cinnabar-render/window.hpp>

namespace ce {
	class RenderEngine {
	 public:
		RenderEngine();
		~RenderEngine();

		void setFramebufferSize(glm::vec2 size);

		void setRenderOption(RenderOption option, bool enable); // TODO: create enum for option

		void setClearColor(glm::vec4 color);
		void setClearDepth(glm::float32 depth);
		void setClearStencil(glm::int32 stencil);

		void setDepthFunc(DepthFunc func);

		void clear(BufferBit buffer = DEPTH_BUFFER_BIT);
		void render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);

	 private:
		void bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
