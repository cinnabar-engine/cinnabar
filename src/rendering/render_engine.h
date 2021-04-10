#pragma once

#include "camera.h"
#include "material.h"
#include <ce_event_handler.h>
#include <core/window.h>
#include <math/transform.h>
#include <vector>

namespace ce {
	struct RenderCommand {
		Transform* transform;
		Material* material;
		Mesh* mesh;
		unsigned points;
	};

	class RenderEngine {
	 private:
		double m_aspectRatio, m_fov, m_near, m_far;

		Camera* m_camera;

		std::vector<RenderCommand> m_commands = {};

		void clear();
		void bind(RenderCommand command);
		void render(unsigned count);
		void unbind(RenderCommand command);

	 public:
		RenderEngine();
		~RenderEngine();

		void setFOV(float fov) { m_fov = glm::radians(fov); };
		void setClipRange(float near, float far) {
			m_near = near;
			m_far = far;
		}
		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);
		void setCamera(Camera* camera) { m_camera = camera; }

		glm::mat4 getProjection();

		void registerCommand(RenderCommand command) {
			m_commands.push_back(command);
		}
		void render();
	};
}
