#pragma once

#include <math/transform.h>

namespace ce {
	class Camera {
	 public:
		Camera();
		~Camera();

		glm::mat4 getView();
		glm::vec3 getRight();
		Transform* getTransform() { return m_transform; }

		void limitPitch();
		void sendToShader(ce::Shader* shader);
	 private:
		ce::Transform* m_transform;
		double speed;
		float fov;
	};
}
