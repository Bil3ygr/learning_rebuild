#pragma once

#include "scene_depth.h"

class SceneStencil : public SceneDepth
{
public:
	SceneStencil(char *name) : SceneDepth(name) {}
	~SceneStencil();

	void onEnter();
	void onExit();
	void update(float time);

protected:
	Controller *m_pStencilController;
};
