#pragma once

#include "controller.h"
#include "scene.h"

class SceneLight : public Scene
{
public:
    SceneLight(char *name) : Scene(name) {}
    ~SceneLight();

    void onEnter();
    void onExit();
    void update(float time);

private:
    Controller *m_pObjectController;
    Controller *m_pLightController;
};
