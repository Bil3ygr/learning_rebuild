#include "scene_depth.h"
#include "camera.h"

SceneDepth::~SceneDepth()
{
    delete m_pCubeController;
    delete m_pPlaneController;
}

void SceneDepth::onEnter()
{
    Camera &camera = Camera::get_instance();
    camera.setEnable(true);

    m_pCubeController = new Controller("shader/cubevs.glsl", "shader/texfs.glsl");
    // m_pCubeController = new Controller("shader/cubevs.glsl", "shader/depthfs.glsl");
    m_pCubeController->addTexture("res/marble.jpg");
    m_pCubeController->setDepthEnable(true);
    m_pCubeController->setStencilEnable(true);
    m_pCubeController->setClearColor(0.1f, 0.1f, 0.1f);
    m_pCubeController->setStencilOptions(GL_ALWAYS, 1, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);
    m_pCubeController->setStencilMask(0xff);

    m_pPlaneController = new Controller("shader/cubevs.glsl", "shader/texfs.glsl");
    // m_pPlaneController = new Controller("shader/cubevs.glsl", "shader/depthfs.glsl");
    m_pPlaneController->addTexture("res/metal.png");
    m_pPlaneController->setDepthEnable(true);
    m_pPlaneController->setStencilEnable(true);
    m_pPlaneController->setClearColor(0.1f, 0.1f, 0.1f);
    m_pPlaneController->setStencilOptions(GL_ALWAYS, 0, 0xff, GL_KEEP, GL_KEEP, GL_REPLACE);
    m_pPlaneController->setStencilMask(0xff);

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
        5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

    int pointers[] = {3, 2};
    bool pointer_enable[] = {true, true};

    m_pCubeController->setVertexInfo(
        cubeVertices, sizeof(cubeVertices),
        pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);

    m_pPlaneController->setVertexInfo(
        planeVertices, sizeof(planeVertices),
        pointers, sizeof(pointers) / sizeof(pointers[0]), pointer_enable);
}

void SceneDepth::onExit()
{
}

void SceneDepth::update(float time)
{
    Camera &camera = Camera::get_instance();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection();

    // plane
    m_pPlaneController->update();

    m_pPlaneController->activeTexture(GL_TEXTURE0, 0);
    m_pPlaneController->m_pShader->setInt("texture1", 0);
    m_pPlaneController->m_pShader->setMat4("model", model);
    m_pPlaneController->m_pShader->setMat4("view", view);
    m_pPlaneController->m_pShader->setMat4("projection", projection);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // cubes
    m_pCubeController->update(false);

    m_pCubeController->activeTexture(GL_TEXTURE0, 0);
    m_pCubeController->m_pShader->setInt("texture1", 0);
    m_pCubeController->m_pShader->setMat4("view", view);
    m_pCubeController->m_pShader->setMat4("projection", projection);

    model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
    m_pCubeController->m_pShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
    m_pCubeController->m_pShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
