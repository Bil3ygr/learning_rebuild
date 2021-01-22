#include "scene_light.h"
#include "camera.h"

SceneLight::~SceneLight()
{
	delete m_pObjectController;
	delete m_pLightController;
}

void SceneLight::onEnter()
{
	Camera &camera = Camera::get_instance();
	camera.setEnable(true);

	m_pObjectController = new Controller("shader/objectvs.glsl", "shader/objectfs.glsl");
	m_pObjectController->addTexture("res/container2.png");
	m_pObjectController->addTexture("res/container2_specular.png");
	m_pObjectController->setDepthEnable(true);
	m_pObjectController->setClearColor(0.1f, 0.1f, 0.1f);

	m_pLightController = new Controller("shader/lampvs.glsl", "shader/lampfs.glsl");
	m_pLightController->setDepthEnable(true);

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

	int pointers[] = {
		3, 3, 2};

	bool object_pointer_enable[] = {
		true, true, true};

	bool light_pointer_enable[] = {
		true, false, false};

	m_pObjectController->setVertexInfo(
		vertices, sizeof(vertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), object_pointer_enable);

	m_pLightController->setVertexInfo(
		vertices, sizeof(vertices),
		pointers, sizeof(pointers) / sizeof(pointers[0]), light_pointer_enable);

	m_pObjectController->activeTexture(GL_TEXTURE1, 0);
	m_pObjectController->activeTexture(GL_TEXTURE2, 1);
	m_pObjectController->m_pShader->setInt("material.diffuse", 1);
	m_pObjectController->m_pShader->setInt("material.specular", 2);
	m_pObjectController->m_pShader->setFloat("material.shininess", 64.0f);
}

void SceneLight::onExit()
{
}

void SceneLight::update(float time)
{
	Camera &camera = Camera::get_instance();

	m_pObjectController->update();

	m_pObjectController->m_pShader->setVec3("viewPos", camera.getPos());
	m_pObjectController->m_pShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	//m_pObjectController->m_pShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	//m_pObjectController->m_pShader->setVec3("lightPos", lightPos);
	// material
	//m_pObjectController->m_pShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	//m_pObjectController->m_pShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	//m_pObjectController->m_pShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);

	//// light
	//m_pObjectController->m_pShader->setInt("light.type", 1);
	//m_pObjectController->m_pShader->setVec3("light.direction", -0.2f, -1.0f, -0.3f);
	////m_pObjectController->m_pShader->setVec3("light.position", lightPos);
	//m_pObjectController->m_pShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	//m_pObjectController->m_pShader->setVec3("light.diffuse", 0.5f, 0.5, 0.5f);
	//m_pObjectController->m_pShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	//glm::vec3 lightColor = glm::vec3(1.0f);
	//lightColor.x = sin(glfwGetTime() * 2.0f);
	//lightColor.y = sin(glfwGetTime() * 0.7f);
	//lightColor.z = sin(glfwGetTime() * 1.3f);
	//glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	//glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	//m_pObjectController->m_pShader->setVec3("light.ambient", ambientColor);
	//m_pObjectController->m_pShader->setVec3("light.diffuse", diffuseColor);

	// spotlight
	m_pObjectController->m_pShader->setVec3("light.direction", camera.getFront());
	m_pObjectController->m_pShader->setVec3("light.position", camera.getPos());
	m_pObjectController->m_pShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
	m_pObjectController->m_pShader->setFloat("light.outCutOff", glm::cos(glm::radians(17.5f)));
	m_pObjectController->m_pShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	m_pObjectController->m_pShader->setVec3("light.diffuse", 0.5f, 0.5, 0.5f);
	m_pObjectController->m_pShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.getView();
	glm::mat4 projection = camera.getProjection();
	m_pObjectController->m_pShader->setMat4("model", model);
	m_pObjectController->m_pShader->setMat4("view", view);
	m_pObjectController->m_pShader->setMat4("projection", projection);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_pLightController->update(false);

	model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.2f));
	m_pLightController->m_pShader->setMat4("model", model);
	m_pLightController->m_pShader->setMat4("view", view);
	m_pLightController->m_pShader->setMat4("projection", projection);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
