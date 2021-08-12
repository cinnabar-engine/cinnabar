#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

ce::Camera::Camera()
	: transform(NULL),
	  fov(glm::radians(75.0)),
	  nearClip(0.1),
	  farClip(100.0) {
	this->transform = new Transform();
}

ce::Camera::~Camera() {
	delete this->transform;
}

glm::mat4 ce::Camera::getViewMatrix() {
	glm::vec3
		pos = -this->transform->getPosition(),
		rotation = -this->transform->getRotation();

	glm::mat4 transformMatrix(1.0f);

	// Rotation
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
	transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw

	// Translation
	transformMatrix = glm::translate(transformMatrix, pos);

	return transformMatrix;
}

void ce::Camera::limitPitch() {
	// TODO: this shouldn't be part of camera, this is related to movement and should be added to the movement scripts
	float cameraPitch = this->transform->getPitch();
	if (cameraPitch > 90.0f)
		cameraPitch = 90.0f;
	if (cameraPitch < -90.0f)
		cameraPitch = -90.0f;
	this->transform->setPitch(cameraPitch);
}

void ce::Camera::sendToShader(ce::Shader* shader, double aspectRatio) {
	shader->setUniform("transform.view", getViewMatrix());
	shader->setUniform("transform.proj", getProjection(aspectRatio));
}
