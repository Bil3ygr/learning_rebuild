#pragma once

#include "controller.h"
#include "scene.h"

class SceneTextureRect : public Scene
{
public:
	SceneTextureRect(char *name) : Scene(name) {}
	~SceneTextureRect();

	void onEnter();
	void onExit();
	void update(float time);

private:
	Controller *m_pController;
};
