#include "scenecontroller.h"
#include "scene_colorrect.h"
#include "scene_cube.h"
#include "scene_depth.h"
#include "scene_light.h"
#include "scene_model.h"
#include "scene_texturerect.h"

void createColorRect(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	char *name = "ColorRect";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneColorRect *scene = new SceneColorRect(name);
		mgr.setScene((Scene *)scene);
	}
}

void createTextureRect(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	char *name = "TextureRect";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneTextureRect *scene = new SceneTextureRect(name);
		mgr.setScene((Scene *)scene);
	}
}

void createCube(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	char *name = "Cube";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneCube *scene = new SceneCube(name);
		mgr.setScene((Scene *)scene);
	}
}

void createLight(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	char *name = "Light";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneLight *scene = new SceneLight(name);
		mgr.setScene((Scene *)scene);
	}
}

void createModel(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	char *name = "Model";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneModel *scene = new SceneModel(name);
		mgr.setScene((Scene *)scene);
	}
}

void createDepth(GLFWwindow *window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	char *name = "Depth";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneDepth *scene = new SceneDepth(name);
		mgr.setScene((Scene *)scene);
	}
}

void switchDepthStencil()
{
	char *name = "Depth";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene != nullptr && strcmp(current_scene->getName(), name) == 0)
	{
		SceneDepth *scene = static_cast<SceneDepth *>(current_scene);
		scene->switchStencilEnable();
	}
}

void switchDepthBlend()
{
	char *name = "Depth";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene != nullptr && strcmp(current_scene->getName(), name) == 0)
	{
		SceneDepth *scene = static_cast<SceneDepth *>(current_scene);
		scene->switchBlendEnable();
	}
}

void switchScene(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		createColorRect(window);
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		createTextureRect(window);
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		createCube(window);
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		createLight(window);
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		createModel(window);
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		createDepth(window);
	else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		switchDepthStencil();
	else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		switchDepthBlend();
}
