#include "scene_texturerect.h"
#include "camera.h"

SceneTextureRect::~SceneTextureRect()
{
	delete m_pController;
}

void SceneTextureRect::onEnter()
{
	Camera &camera = Camera::get_instance();
	camera.setEnable(false);

	m_pController = new Controller("shader/texvs.glsl", "shader/texfs.glsl");
	m_pController->addTexture("res/container.jpg");
	m_pController->setClearColor(0.3f, 0.2f, 0.3f);

	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // 右上
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // 左上
	};

	int pointers[] = {
		3, 3, 2};

	bool pointer_enable[] = {
		true, true, true};

	int indices[] = {
		0, 1, 3,
		1, 2, 3};

	m_pController->setVertexInfo(
		vertices, sizeof(vertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable,
		indices, sizeof(indices));
}

void SceneTextureRect::onExit()
{
}

void SceneTextureRect::update(float time)
{
	m_pController->update();

	m_pController->activeTexture(GL_TEXTURE0, 0);
	m_pController->m_pShader->setInt("texture1", 0);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	float scale = abs((float)sin(glfwGetTime()));
	trans = glm::scale(trans, glm::vec3(scale, scale, scale));
	m_pController->m_pShader->setMat4("transform", trans);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
