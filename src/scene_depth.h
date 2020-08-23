#pragma once

#include "controller.h"
#include "scene.h"

class SceneDepth : public Scene
{
public:
	SceneDepth(char *name) : Scene(name) {}
	~SceneDepth();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pCubeController;
	Controller *m_pPlaneController;
};
