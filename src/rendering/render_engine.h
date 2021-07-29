#pragma once

#include "camera.h"
#include "material.h"
#include <ce_event_handler.h>
#include <core/window.h>
#include <math/transform.h>
#include <vector>

// TODO: seperate camera from RenderEngine. make camera part of rendercommand

namespace ce {
	struct RenderCommand {
		Transform* transform;
		Material* material;
		Mesh* mesh;
		Camera* camera;
	};

	class RenderEngine {
	 public:
		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);
		double getAspectRatio() { return m_aspectRatio; };

		void registerCommand(RenderCommand command);
		void render();

	 private:
		double m_aspectRatio; // TODO: aspect ratio shouldn't be stored, the Camera should store a projection matrix and it should be left to the user (programmer) to recalculate the projection matrix (using Camera functions) when the window size changes

		std::vector<RenderCommand> m_commands = {};

		void clear();
		void
			bind(RenderCommand command),
			unbind(RenderCommand command);
	};
}
