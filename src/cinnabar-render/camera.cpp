#include <cinnabar-render/camera.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cinnabar-render/shader.hpp>

ce::Camera::Camera(ce::Transform* transform)
	: transform(transform) {}

ce::Camera::~Camera() {
	//delete this->transform;
	// TODO: figure out when to delete transform
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

void ce::Camera::sendToShader(ce::Shader* shader) {
	shader->setUniform("transform.view", getViewMatrix());
	shader->setUniform("transform.proj", this->projection);
}
