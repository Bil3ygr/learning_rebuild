#include "scene_colorrect.h"
#include "../camera.h"

SceneColorRect::~SceneColorRect()
{
	delete m_pController;
}

void SceneColorRect::onEnter()
{
	Camera &camera = Camera::get_instance();
	camera.setEnable(false);

	m_pController = new Controller("shader/vs.glsl", "shader/fs.glsl");
	m_pController->setClearColor(0.2f, 0.3f, 0.3f);

	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f};

	int pointers[] = {
		3, 3};

	int indices[] = {
		0, 2, 3,
		0, 1, 2};

	m_pController->setVertexInfo(vertices, pointers, indices);
}

void SceneColorRect::onExit()
{
}

void SceneColorRect::update(float time)
{
	m_pController->update();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
