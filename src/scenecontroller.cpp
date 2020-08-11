#include "scenecontroller.h"
#include "scene_colorrect.h"
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
