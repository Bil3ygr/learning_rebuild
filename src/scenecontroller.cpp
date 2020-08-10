#include "scenecontroller.h"
#include "scene_colorrect.h"

void createColorRect()
{
	char *name = "ColorRect";
	SceneMgr &mgr = SceneMgr::get_instance();
	Scene *current_scene = mgr.getCurrentScene();

	if (current_scene == nullptr || strcmp(current_scene->getName(), name) != 0)
	{
		SceneColorRect *scene = new SceneColorRect(name);
		mgr.setScene((Scene *)scene);
	}
}
