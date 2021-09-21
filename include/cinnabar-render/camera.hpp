#pragma once

#include <glm/glm.hpp>

#include <cinnabar-core/transform.hpp>

#include <cinnabar-render/shader.hpp>

namespace ce {
	class Camera {
	 public:
		Camera();
		~Camera();

		glm::mat4 getViewMatrix();

		void sendToShader(ce::Shader* shader);

		ce::Transform* transform;
		glm::mat4 projection;
	};
}
