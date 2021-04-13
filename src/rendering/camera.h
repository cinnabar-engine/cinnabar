#pragma once

#include <math/transform.h>

namespace ce {
	class Camera {
	 public:
		Camera();
		~Camera();

		glm::mat4 getView();
		glm::vec3 getRight();
		void sendToShader(ce::Shader* shader);
		Transform* getTransform() { return m_transform; }
		void boundPitch();
	 private:
		ce::Transform* m_transform;
		double speed;
		float fov;
	};
}
