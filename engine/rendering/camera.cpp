#include "camera.h"

ce::Camera::Camera()
:m_transform(NULL)
{
	m_transform = new Transform();
}

ce::Camera::~Camera()
{
	delete m_transform;
}

glm::mat4 ce::Camera::getView()
{
	glm::vec3
		pos = m_transform->getPosition(),
		forward = m_transform->getForward();
	return glm::lookAt(pos,pos+forward,ce::Transform::GetGlobalUp());
}

glm::vec3 ce::Camera::getRight()
{
	glm::vec3
		forward = m_transform->getForward(),
		up = ce::Transform::GetGlobalUp();
	return glm::normalize(glm::cross(forward,up));
}

void ce::Camera::sendToShader(ce::Shader* shader)
{
	shader->setMat4("transform.view",getView());
}

void ce::Camera::boundPitch()
{
	float cameraPitch = m_transform->getPitch();
	if (cameraPitch > 89.9f) // TODO: fix broken 90 degree pitch
		cameraPitch = 89.9f;
	if (cameraPitch < -89.9f)
		cameraPitch = -89.9f;
	m_transform->setPitch(cameraPitch);
}

