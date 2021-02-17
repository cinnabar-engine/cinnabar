#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_

#include "material.h"
#include <ce_event_handler.h>
#include <core/window.h>
#include <math/transform.h>
#include <vector>
#include "camera.h"

namespace ce {
	struct RenderCommand {
		Transform* transform;
		Material* material;
		Mesh* mesh;
		unsigned points;
	};

	class RenderingEngine {
	 private:
		float m_aspectRatio, m_fov, m_near, m_far;
		
		Camera* m_camera;

		std::vector<RenderCommand> m_commands = {};

		void clear();
		void bind(RenderCommand command);
		void render(unsigned count);
		void unbind(RenderCommand command);

	 public:
		RenderingEngine();
		~RenderingEngine();

		void setFOV(float fov) { m_fov = glm::radians(fov); };
		void setClipRange(float near, float far) {
			m_near = near;
			m_far = far;
		}
		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);
		void setCamera(Camera* camera){m_camera = camera;}

		glm::mat4 getProjection();

		void registerCommand(RenderCommand command) {
			m_commands.push_back(command);
		}
		void render();
	};
}

#endif // _RENDER_ENGINE_H_
