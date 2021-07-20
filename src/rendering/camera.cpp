#include "camera.h"

ce::Camera::Camera()
	: m_transform(NULL) {
	m_transform = new Transform();
}

ce::Camera::~Camera() {
	delete m_transform;
}

glm::mat4 ce::Camera::getView() {
	glm::vec3
		pos = m_transform->getPosition(),
		forward = m_transform->getForward();
	return glm::lookAt(pos, pos + forward, ce::Transform::GetGlobalUp());
}

glm::vec3 ce::Camera::getRight() {
	glm::vec3
		forward = m_transform->getForward(),
		up = ce::Transform::GetGlobalUp();
	return glm::normalize(glm::cross(forward, up));
}

// TODO: this needs to be edited when renderEngine is seperated from camera
void ce::Camera::sendToShader(ce::Shader* shader) {
	shader->setUniform("transform.view", getView());
}

void ce::Camera::limitPitch() {
	// TODO: this shouldn't be part of camera, this is related to movement and should be added to the movement scripts
	float cameraPitch = m_transform->getPitch();
	if (cameraPitch > 89.9f) // TODO: fix broken 90 degree pitch
		cameraPitch = 89.9f;
	if (cameraPitch < -89.9f)
		cameraPitch = -89.9f;
	m_transform->setPitch(cameraPitch);
}