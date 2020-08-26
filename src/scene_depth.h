#pragma once

#include "controller.h"
#include "scene.h"
#include <vector>

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
	Controller *m_pGrassController;

	std::vector<glm::vec3> m_vVegetation;
};
