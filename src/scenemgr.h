#pragma once

#include "main.h"
#include "scene.h"

class SceneMgr
{
public:
	~SceneMgr() {}
	SceneMgr(const SceneMgr &) = delete;
	SceneMgr &operator=(const SceneMgr &) = delete;
	static SceneMgr &get_instance();

	void setScene(Scene *scene);
	Scene *getCurrentScene();
	void update(float time);
	void clearScene();

private:
	SceneMgr() {}

	Scene *m_pScene = nullptr;
};

void sceneUpdate(float time);
