#pragma once

#include "controller.h"
#include "scene.h"

class SceneCube : public Scene
{
public:
	SceneCube(char *name) : Scene(name) {}
	~SceneCube();

	void onEnter();
	void onExit();
	void update(float time);

private:
	Controller *m_pController;
};
