#pragma once

class Scene
{
public:
	Scene(char *name) : m_cName(name) {}
	~Scene() {}

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void update(float time) = 0;
	char *getName();

private:
	char *m_cName;
};