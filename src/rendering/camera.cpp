#include "camera.h"

ce::Camera::Camera()
	: m_transform(NULL) {
	m_transform = new Transform();
}

ce::Camera::~Camera() {
	delete m_transform;
}

glm::mat4 ce::Camera::getViewMatrix() {
	glm::vec3
		pos = -m_transform->getPosition(),
		rotation = -m_transform->getRotation();
	
	glm::mat4 transform(1.0f);

	// Rotation
	transform = glm::rotate(transform, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll
	transform = glm::rotate(transform, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
	transform = glm::rotate(transform, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw

	// Translation
	transform = glm::translate(transform, pos);

	return transform;
}

// TODO: this needs to be edited when renderEngine is seperated from camera
void ce::Camera::sendToShader(ce::Shader* shader) {
	shader->setUniform("transform.view", getViewMatrix());
}

void ce::Camera::limitPitch() {
	// TODO: this shouldn't be part of camera, this is related to movement and should be added to the movement scripts
	float cameraPitch = m_transform->getPitch();
	if (cameraPitch > 90.0f)
		cameraPitch = 90.0f;
	if (cameraPitch < -90.0f)
		cameraPitch = -90.0f;
	m_transform->setPitch(cameraPitch);
}