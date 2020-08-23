#pragma once

#include "scene.h"
#include "controller.h"

class SceneTextureRect : public Scene
{
public:
	SceneTextureRect(char *name) : Scene(name) {}
	~SceneTextureRect();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pController;
};
