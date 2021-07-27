#include "transform.h"

ce::Transform::Transform()
	: m_pos(0.0f, 0.0f, 0.0f), m_rot(0.0f, 0.0f, 0.0f),
	  m_scale(1.0f, 1.0f, 1.0f), m_parent(NULL) {}

ce::Transform::~Transform() {}

glm::mat4 ce::Transform::getMatrix() {
	glm::mat4 transform(1.0f);
	if (m_parent != NULL) {
		transform = m_parent->getMatrix();
	}

	// Translation
	transform = glm::translate(transform, m_pos);

	// Rotation
	// TODO: Quaternions
	transform = glm::rotate(transform, glm::radians(getYaw()), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
	transform = glm::rotate(transform, glm::radians(getPitch()), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
	transform = glm::rotate(transform, glm::radians(getRoll()), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

	// Scale
	transform = glm::scale(transform, m_scale);

	return transform;
}

void ce::Transform::sendToShader(ce::Shader* shader) {
	shader->setUniform("transform.model", getMatrix());
}

#include <core/tpnt_log.h>
#include <limits>

glm::vec3 ce::Transform::getForward(bool useYaw, bool usePitch, bool) {
	float
		yaw = useYaw ? glm::radians(getYaw()) : 0.0,
		pitch = usePitch ? glm::radians(getPitch()) : 0.0;
	return glm::vec3(
		-sin(yaw) * cos(pitch),
		sin(pitch),
		-cos(yaw) * cos(pitch));
}
glm::vec3 ce::Transform::getRight(bool useYaw, bool usePitch, bool useRoll) {
	float
		yaw = useYaw ? glm::radians(getYaw()) : 0.0,
		pitch = usePitch ? glm::radians(getPitch()) : 0.0,
		roll = useRoll ? glm::radians(getRoll()) : 0.0;
	return glm::vec3(
		cos(yaw) * cos(roll) + sin(yaw) * sin(roll) * sin(pitch),
		sin(roll) * cos(pitch),
		-sin(yaw) * cos(roll) + cos(yaw) * sin(roll) * sin(pitch));
}
glm::vec3 ce::Transform::getUp(bool useYaw, bool usePitch, bool useRoll) {
	float
		yaw = useYaw ? glm::radians(getYaw()) : 0.0,
		pitch = usePitch ? glm::radians(getPitch()) : 0.0,
		roll = useRoll ? glm::radians(getRoll()) : 0.0;
	return glm::vec3(
		-cos(yaw) * sin(roll) + sin(yaw) * sin(pitch) * cos(roll),
		cos(roll) * cos(pitch),
		sin(yaw) * sin(roll) + cos(yaw) * sin(pitch) * cos(roll));
}
