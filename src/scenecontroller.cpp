#include "scenecontroller.h"
#include "scene_colorrect.h"
#include <iostream>

void createColorRect()
{
	char *name = "ColorRect";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	std::cout << *(current_scene->getName()) << std::endl;
	std::cout << *name << std::endl;
	if (current_scene)
		std::cout << (*(current_scene->getName()) == *name) << std::endl;

	if (current_scene == nullptr || *(current_scene->getName()) != *name)
	{
		SceneColorRect *scene = new SceneColorRect(name);
		mgr.setScene((Scene *)scene);
	}
}