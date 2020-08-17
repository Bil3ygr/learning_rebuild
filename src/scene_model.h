#pragma once

#include "scene.h"
#include "controller.h"
#include "model.h"

class SceneModel : public Scene
{
public:
	SceneModel(char *name) : Scene(name) {}
	~SceneModel();

	void onEnter();
	void onExit();
	void update(float time);

private:
	Controller *m_pController;
	Model *m_pModel;
};
