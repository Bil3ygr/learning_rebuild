#pragma once

#include "scene.h"
#include "controller.h"

class SceneColorRect : public Scene
{
public:
	SceneColorRect(char *name) : Scene(name) {}
	~SceneColorRect();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pController;
};
