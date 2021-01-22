#include "scene_depth.h"
#include "camera.h"
#include <map>

SceneDepth::~SceneDepth()
{
	delete m_pPlaneController;
	delete m_pCubesController;
	delete m_pStencilsController;
	delete m_pGrassesController;
	delete m_pWindowsController;
}

void SceneDepth::onEnter()
{
	Camera &camera = Camera::get_instance();
	camera.setEnable(true);

	initPlaneController();
	initCubesController();
	initStencilsController();
	initGrassesController();
	initWindowsController();

	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

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

	float transparentVertices[] = {
		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f};

	int pointers[] = {3, 2};
	bool pointer_enable[] = {true, true};

	m_pPlaneController->setVertexInfo(
		planeVertices, sizeof(planeVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

	m_pCubesController->setVertexInfo(
		cubeVertices, sizeof(cubeVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

	m_pStencilsController->setVertexInfo(
		cubeVertices, sizeof(cubeVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

	m_pGrassesController->setVertexInfo(
		transparentVertices, sizeof(transparentVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

	m_pWindowsController->setVertexInfo(
		transparentVertices, sizeof(transparentVertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

	m_vPositions.clear();
	m_vPositions.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	m_vPositions.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	m_vPositions.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	m_vPositions.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	m_vPositions.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
}

void SceneDepth::onExit()
{
}

void SceneDepth::update(float time)
{
	drawPlane();
	drawCubes();
	if (m_bStencilEnable)
		drawStencils();
	if (m_bBlendEnable)
		drawWindows();
}

void SceneDepth::switchStencilEnable()
{
	m_bStencilEnable = !m_bStencilEnable;
	if (m_bStencilEnable)
		m_bBlendEnable = false;
}

void SceneDepth::switchBlendEnable()
{
	m_bBlendEnable = !m_bBlendEnable;
	if (m_bBlendEnable)
		m_bStencilEnable = false;
}

void SceneDepth::initPlaneController()
{
	m_pPlaneController = new Controller("shader/cubevs.glsl", "shader/texfs.glsl");
	m_pPlaneController->setClearColor(0.1f, 0.1f, 0.1f);
	// m_pPlaneController = new Controller("shader/cubevs.glsl", "shader/depthfs.glsl");
	m_pPlaneController->addTexture("res/metal.png");
	m_pPlaneController->setDepthEnable(true);
	m_pPlaneController->setStencilEnable(true);
	m_pPlaneController->setStencilOptions(GL_ALWAYS, 0, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);

	m_pPlaneController->activeTexture(GL_TEXTURE0, 0);
	m_pPlaneController->m_pShader->setInt("texture1", 0);
}

void SceneDepth::drawPlane()
{
	Camera &camera = Camera::get_instance();

	// plane
	m_pPlaneController->update();
	m_pPlaneController->m_pShader->setMat4("model", glm::mat4(1.0f));
	m_pPlaneController->m_pShader->setMat4("view", camera.getView());
	m_pPlaneController->m_pShader->setMat4("projection", camera.getProjection());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SceneDepth::initCubesController()
{
	m_pCubesController = new Controller("shader/cubevs.glsl", "shader/texfs.glsl");
	// m_pCubesController = new Controller("shader/cubevs.glsl", "shader/depthfs.glsl");
	m_pCubesController->addTexture("res/marble.jpg");
	m_pCubesController->setDepthEnable(true);
	m_pCubesController->setStencilEnable(true);
	m_pCubesController->setStencilOptions(GL_ALWAYS, 1, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);

	m_pCubesController->activeTexture(GL_TEXTURE0, 0);
	m_pCubesController->m_pShader->setInt("texture1", 0);
}

void SceneDepth::drawCubes()
{
	Camera &camera = Camera::get_instance();
	glm::mat4 model;

	m_pCubesController->update(false);
	m_pCubesController->m_pShader->setMat4("view", camera.getView());
	m_pCubesController->m_pShader->setMat4("projection", camera.getProjection());

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
	m_pCubesController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
	m_pCubesController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SceneDepth::initStencilsController()
{
	m_pStencilsController = new Controller("shader/cubevs.glsl", "shader/stencilfs.glsl");
	m_pStencilsController->addTexture("res/marble.jpg");
	m_pStencilsController->setDepthEnable(true);
	m_pStencilsController->setStencilEnable(true);
	m_pStencilsController->setStencilOptions(GL_NOTEQUAL, 1, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);
	m_pStencilsController->setStencilMask(0x00);

	m_pStencilsController->activeTexture(GL_TEXTURE0, 0);
	m_pStencilsController->m_pShader->setInt("texture1", 0);
	m_pStencilsController->m_pShader->setVec4("stencilColor", 0.04f, 0.28f, 0.26f, 1.0f);
}

void SceneDepth::drawStencils()
{
	Camera &camera = Camera::get_instance();
	glm::mat4 model;
	float scale = 1.1f;

	m_pStencilsController->update(false);
	m_pStencilsController->m_pShader->setMat4("view", camera.getView());
	m_pStencilsController->m_pShader->setMat4("projection", camera.getProjection());

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	m_pStencilsController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	m_pStencilsController->m_pShader->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SceneDepth::initGrassesController()
{
	m_pGrassesController = new Controller("shader/cubevs.glsl", "shader/alphafs.glsl");
	m_pGrassesController->addTexture("res/grass.png");
	m_pGrassesController->setDepthEnable(true);
	m_pGrassesController->setBlendEnable(true);

	m_pGrassesController->activeTexture(GL_TEXTURE0, 0);
	m_pGrassesController->m_pShader->setInt("texture1", 0);
	m_pGrassesController->m_pShader->setFloat("alpha", 0.1f);
}

void SceneDepth::drawGrasses()
{
	Camera &camera = Camera::get_instance();
	glm::mat4 model;

	m_pGrassesController->update(false);
	m_pGrassesController->m_pShader->setMat4("view", camera.getView());
	m_pGrassesController->m_pShader->setMat4("projection", camera.getProjection());

	std::map<float, glm::vec3> sorted;

	for (int i = 0; i < m_vPositions.size(); i++)
	{
		float distance = glm::length(camera.getPos() - m_vPositions[i]);
		sorted[distance] = m_vPositions[i];
	}

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
	{
		model = glm::translate(glm::mat4(1.0f), it->second);
		m_pGrassesController->m_pShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void SceneDepth::initWindowsController()
{
	m_pWindowsController = new Controller("shader/cubevs.glsl", "shader/texfs.glsl");
	m_pWindowsController->addTexture("res/window.png");
	m_pWindowsController->setDepthEnable(true);
	m_pWindowsController->setBlendEnable(true);

	m_pWindowsController->activeTexture(GL_TEXTURE0, 0);
	m_pWindowsController->m_pShader->setInt("texture1", 0);
}

void SceneDepth::drawWindows()
{
	Camera &camera = Camera::get_instance();
	glm::mat4 model;

	m_pWindowsController->update(false);
	m_pWindowsController->m_pShader->setMat4("view", camera.getView());
	m_pWindowsController->m_pShader->setMat4("projection", camera.getProjection());

	std::map<float, glm::vec3> sorted;

	for (int i = 0; i < m_vPositions.size(); i++)
	{
		float distance = glm::length(camera.getPos() - m_vPositions[i]);
		sorted[distance] = m_vPositions[i];
	}

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
	{
		model = glm::translate(glm::mat4(1.0f), it->second);
		m_pWindowsController->m_pShader->setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
