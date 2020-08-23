#include "scene_stencil.h"
#include "camera.h"

SceneStencil::~SceneStencil()
{
	delete m_pStencilController;
}

void SceneStencil::onEnter()
{
	SceneDepth::onEnter();

	m_pStencilController = new Controller("shader/cubevs.glsl", "shader/colorfs.glsl");
	m_pStencilController->addTexture("res/marble.jpg");
	m_pStencilController->setStencilEnable(true);
	m_pStencilController->setStencilOptions(GL_NOTEQUAL, 1, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);
	m_pStencilController->setStencilMask(0x00);

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

	int pointers[] = {3, 2};
	bool pointer_enable[] = {true, true};

	m_pStencilController->setVertexInfo(
		cubeVertices, sizeof(cubeVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);
}

void SceneStencil::onExit()
{
}

void SceneStencil::update(float time)
{
	SceneDepth::update(time);

	Camera &camera = Camera::get_instance();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.getView();
	glm::mat4 projection = camera.getProjection();
	// strokes
	float scale = 1.1f;
	m_pStencilController->update(false);

	m_pStencilController->activeTexture(GL_TEXTURE0, 0);
	m_pStencilController->m_pShader->setInt("texture1", 0);
	m_pStencilController->m_pShader->setMat4("view", view);
	m_pStencilController->m_pShader->setMat4("projection", projection);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	m_pStencilController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	m_pStencilController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
