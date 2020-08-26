#pragma once

#include "controller.h"
#include "scene.h"

class SceneDepth : public Scene
{
public:
	SceneDepth(char *name) : Scene(name) {}
	~SceneDepth();

	void onEnter();
	void onExit();
	void update(float time);

	void switchStencilEnable();
	void switchBlendEnable();

protected:
	void initPlaneController();
	void drawPlane();
	void initCubesController();
	void drawCubes();
	void initStencilsController();
	void drawStencils();
	void initGrassesController();
	void drawGrasses();
	void initWindowsController();
	void drawWindows();

	Controller *m_pPlaneController;
	Controller *m_pCubesController;
	Controller *m_pStencilsController;
	Controller *m_pGrassesController;
	Controller *m_pWindowsController;

	std::vector<glm::vec3> m_vPositions;
	bool m_bStencilEnable = false, m_bBlendEnable = false;
};
