#include "transform.h"

ce::Transform::Transform()
	: m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
	  m_scale(1.0f, 1.0f, 1.0f) {}

ce::Transform::~Transform() {}

glm::mat4 ce::Transform::getMatrix() {
	glm::mat4 transform(1.0f);

	// Scale
	transform = glm::scale(transform, m_scale);

	// Rotation
	// TODO: Quaternions
	transform = glm::rotate(transform, glm::radians(getPitch()),
		glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
	transform = glm::rotate(
		transform, glm::radians(getYaw()), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
	transform = glm::rotate(
		transform, glm::radians(getRoll()), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

	// Translation
	transform = glm::translate(transform, m_pos);

	return transform;
}

void ce::Transform::saveToShader(ce::Shader* shader) {
	shader->setMat4("transform.model", getMatrix());
}
