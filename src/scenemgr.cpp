#include "scenemgr.h"

SceneMgr &SceneMgr::get_instance()
{
	static SceneMgr instance;
	return instance;
}

void SceneMgr::setScene(Scene *scene)
{
	if (m_pScene != nullptr)
	{
		m_pScene->onExit();
		delete m_pScene;
	}

	m_pScene = scene;
	m_pScene->onEnter();
}

Scene *SceneMgr::getCurrentScene()
{
	return m_pScene;
}

void SceneMgr::update(float time)
{
	if (m_pScene != nullptr)
		m_pScene->update(time);
	else
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void SceneMgr::clearScene()
{
	if (m_pScene != nullptr)
	{
		m_pScene->onExit();
		delete m_pScene;
		m_pScene = nullptr;
	}
}

void sceneUpdate(float time)
{
	SceneMgr &mgr = SceneMgr::get_instance();
	mgr.update(time);
}
