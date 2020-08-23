#pragma once

class Scene
{
public:
	Scene(char *name) : m_cName(name) {}
	virtual ~Scene() {}

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void update(float time) = 0;
	char *getName();

protected:
	char *m_cName;
};
