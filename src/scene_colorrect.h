#pragma once

#include "scene.h"
#include "controller.h"

class SceneColorRect : public Scene
{
public:
	SceneColorRect(char *name) : Scene(name) {}

	void onEnter();
	void onExit();
	void update(float time);

private:
	Controller *m_pController;

	void onDraw();
};