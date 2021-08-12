#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <core/transform.hpp>

#include "shader.hpp"

namespace ce {
	class Camera {
	 public:
		Camera();
		~Camera();

		glm::mat4
			getViewMatrix(),
			getProjection(double aspectRatio) { return glm::perspective(this->fov, aspectRatio, this->nearClip, this->farClip); };

		void limitPitch();
		void sendToShader(ce::Shader* shader, double aspectRatio);

		ce::Transform* transform;
		double fov, nearClip, farClip;
	};
}
