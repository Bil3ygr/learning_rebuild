#include "camera.h"

Camera &Camera::get_instance()
{
	static Camera instance;
	return instance;
}

void Camera::initCamera(float width, float height, float fovy, float near, float far)
{
	m_fWidth = width;
	m_fHeight = height;
	m_fZoom = fovy;
	m_fNear = near;
	m_fFar = far;
}

void Camera::setViewPort(float width, float height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	m_fWidth = width;
	m_fHeight = height;
}

void Camera::mouseMove(float xpos, float ypos, GLboolean limit)
{
	if (!m_bEnable)
		return;

	if (m_bFirstMouse)
	{
		m_fLastX = xpos;
		m_fLastY = ypos;
		m_bFirstMouse = false;
		return;
	}

	float xoffset = xpos - m_fLastX;
	float yoffset = m_fLastY - ypos;
	m_fLastX = xpos;
	m_fLastY = ypos;

	m_fYaw += xoffset * m_fSensitivity;
	m_fPitch += yoffset * m_fSensitivity;

	if (limit)
	{
		if (m_fPitch > 89.0f)
			m_fPitch = 89.0f;
		else if (m_fPitch < -89.0f)
			m_fPitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::mouseScroll(float yoffset)
{
	if (!m_bEnable)
		return;

	if (m_fZoom >= 1.0f && m_fZoom <= 45.0f)
		m_fZoom -= yoffset;
	if (m_fZoom <= 1.0f)
		m_fZoom = 1.0f;
	if (m_fZoom >= 45.0f)
		m_fZoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 _front = glm::vec3(1.0f);
	_front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	_front.y = sin(glm::radians(m_fPitch));
	_front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_vFront = glm::normalize(_front);

	m_vRight = glm::normalize(glm::cross(m_vFront, m_vUp));
	m_vRealUp = glm::normalize(glm::cross(m_vRight, m_vFront));
}

void Camera::setEnable(bool enable)
{
	m_bEnable = enable;
}

void Camera::setFrameTime(float time)
{
	m_fFrameTime = time;
}

void Camera::keyMove(CAMERA_DIR dir)
{
	if (!m_bEnable)
		return;

	float velocity = m_fSpeed * m_fFrameTime;
	if (dir == CAMERA_DIR::FORWARD)
		m_vPos += m_vFront * velocity;
	else if (dir == CAMERA_DIR::BACKWARD)
		m_vPos -= m_vFront * velocity;
	else if (dir == CAMERA_DIR::LEFT)
		m_vPos -= m_vRight * velocity;
	else if (dir == CAMERA_DIR::RIGHT)
		m_vPos += m_vRight * velocity;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(m_vPos, m_vPos + m_vFront, m_vRealUp);
}

glm::mat4 Camera::getProjection()
{
	return glm::perspective(glm::radians(m_fZoom), m_fWidth / m_fHeight, m_fNear, m_fFar);
}

glm::vec3 Camera::getPos()
{
	return m_vPos;
}

glm::vec3 Camera::getFront()
{
	return m_vFront;
}

void initCamera(float width, float height, float fovy, float near, float far)
{
	Camera &camera = Camera::get_instance();
	camera.initCamera(width, height, fovy, near, far);
	camera.updateCameraVectors();
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	Camera &camera = Camera::get_instance();
	camera.setViewPort((float)width, (float)height);
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
	Camera &camera = Camera::get_instance();
	camera.mouseMove((float)xpos, (float)ypos);
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	Camera &camera = Camera::get_instance();
	camera.mouseScroll((float)yoffset);
}

void cameraUpdate(float time)
{
	Camera &camera = Camera::get_instance();
	camera.setFrameTime(time);
}

void cameraKeyMove(GLFWwindow *window)
{
	Camera &camera = Camera::get_instance();
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
		camera.keyMove(CAMERA_DIR::FORWARD);
	else if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
		camera.keyMove(CAMERA_DIR::BACKWARD);
	else if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
		camera.keyMove(CAMERA_DIR::LEFT);
	else if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
		camera.keyMove(CAMERA_DIR::RIGHT);
}
