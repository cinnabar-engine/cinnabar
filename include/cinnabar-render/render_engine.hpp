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
		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);

		void
			clear(),
			render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);

	 private:
		void bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
