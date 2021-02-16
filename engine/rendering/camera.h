#ifndef _CE_CAMERA_H_
#define _CE_CAMERA_H_

#include <math/transform.h>

namespace ce {
	class Camera {
	private:
		ce::Transform* m_transform;
		float speed,
		fov;
	public:
		Camera();
		~Camera();
		
		glm::mat4 getView();
		glm::vec3 getRight();
		void sendToShader(ce::Shader* shader);
		Transform* getTransform(){return m_transform;}
	};
}

#endif //_CE_CAMERA_H_
