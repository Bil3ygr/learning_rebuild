#pragma once

#include "controller.h"
#include "model.h"
#include "scene.h"

class SceneModel : public Scene
{
public:
	SceneModel(char *name) : Scene(name) {}
	~SceneModel();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pController;
	Model *m_pModel;
};
