#pragma once

#include "scene.h"
#include "controller.h"

class SceneLight : public Scene
{
public:
    SceneLight(char *name) : Scene(name) {}
    ~SceneLight();

    void onEnter();
    void onExit();
    void update(float time);

protected:
    Controller *m_pObjectController;
    Controller *m_pLightController;
};
