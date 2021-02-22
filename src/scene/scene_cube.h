#pragma once

#include "scene.h"
#include "../controller.h"

class SceneCube : public Scene
{
public:
	SceneCube(char *name) : Scene(name) {}
	~SceneCube();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pController;
};
