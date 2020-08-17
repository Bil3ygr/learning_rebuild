#pragma once

#include "globals.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	~Camera() {}
	Camera(const Camera &) = delete;
	Camera &operator=(const Camera &) = delete;
	static Camera &get_instance();

	void initCamera(float width, float height, float fovy, float near, float far);
	void setViewPort(float width, float height);
	void mouseMove(float xpos, float ypos, GLboolean limit = true);
	void mouseScroll(float yoffset);
	void updateCameraVectors();
	void setEnable(bool enable);
	void setFrameTime(float time);
	void keyMove(CAMERA_DIR dir);

	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::vec3 getPos();
	glm::vec3 getFront();

private:
	Camera() {}

	glm::vec3 m_vPos = glm::vec3(0, 0, 3.0f);
	glm::vec3 m_vFront = glm::vec3(0, 0, -1.0f);
	glm::vec3 m_vUp = glm::vec3(0, 1.0f, 0);
	glm::vec3 m_vRight, m_vRealUp;

	bool m_bEnable = false;
	bool m_bFirstMouse = true;
	float m_fWidth, m_fHeight;
	float m_fLastX, m_fLastY;

	float m_fYaw = -90.f, m_fPitch = 0;
	float m_fSensitivity = 0.1f, m_fSpeed = 2.5f, m_fZoom = 45.0f;
	float m_fNear = 0.1f, m_fFar = 100.0f;

	float m_fFrameTime;
};

void initCamera(float width, float height, float fovy, float nera, float far);

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void cameraUpdate(float time);
void cameraKeyMove(GLFWwindow *window);
