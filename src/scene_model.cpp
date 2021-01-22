#include "scene_model.h"
#include "camera.h"

SceneModel::~SceneModel()
{
	delete m_pController;
}

void SceneModel::onEnter()
{
	Camera &camera = Camera::get_instance();
	camera.setEnable(true);

	m_pController = new Controller("shader/modelvs.glsl", "shader/modelfs.glsl");
	m_pController->setDepthEnable(true);
	m_pController->setClearColor(0.05f, 0.05f, 0.05f);

	m_pModel = new Model("res/nanosuit/nanosuit.obj");
}

void SceneModel::onExit()
{
}

void SceneModel::update(float time)
{
	Camera &camera = Camera::get_instance();

	m_pController->update();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));		// it's a bit too big for our scene, so scale it down
	m_pController->m_pShader->setMat4("model", model);
	m_pController->m_pShader->setMat4("view", camera.getView());
	m_pController->m_pShader->setMat4("projection", camera.getProjection());

	m_pModel->update(m_pController);
}
