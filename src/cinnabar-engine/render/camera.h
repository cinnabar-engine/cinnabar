#pragma once

#include <core/transform.h>

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
