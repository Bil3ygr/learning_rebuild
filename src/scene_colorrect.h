#pragma once

#include "controller.h"
#include "scene.h"

class SceneColorRect : public Scene
{
public:
	SceneColorRect(char *name) : Scene(name) {}
	~SceneColorRect();

	void onEnter();
	void onExit();
	void update(float time);

private:
	Controller *m_pController;
};
