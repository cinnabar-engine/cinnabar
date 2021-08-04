#pragma once

#include "camera.h"
#include "material.h"
#include <ce_event_handler.h>
#include <core/window.h>
#include <math/transform.h>
#include <vector>

namespace ce {
	class RenderEngine {
	 public:
		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);
		double getAspectRatio() { return m_aspectRatio; };

		void
			clear(),
			render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	 private:
		double m_aspectRatio; // TODO: aspect ratio shouldn't be stored, the Camera should store a projection matrix and it should be left to the user (programmer) to recalculate the projection matrix (using Camera functions) when the window size changes

		void
			bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
