#include "main.h"
#include "camera.h"
#include "scenemgr.h"
#include "scenecontroller.h"

GLFWwindow *window = NULL;
bool esc_press = false;

void keyCallback(GLFWwindow *window, int key, int scanecode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
	{
		if (action == GLFW_PRESS)
		{
			if (esc_press)
				return;
			esc_press = true;

			SceneMgr &mgr = SceneMgr::get_instance();
			if (mgr.getCurrentScene() != nullptr)
			{
				mgr.clearScene();
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			else
				glfwSetWindowShouldClose(window, true);
		}
		else
		{
			if (esc_press)
				esc_press = false;
		}
	}
}

bool initGLFW(float width, float height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow((int)width, (int)height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Create window failed" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Init GLAD fialed" << std::endl;
		return false;
	}

	return true;
}

float lastTime = 0;

void loop(float time)
{
	cameraUpdate(time);
	sceneUpdate(time);
}

void processInput()
{
	// if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	// {
	// 	SceneMgr &mgr = SceneMgr::get_instance();
	// 	std::cout << mgr.getCurrentScene() << std::endl;
	// 	std::cout << (mgr.getCurrentScene() == nullptr) << std::endl;
	// 	if (mgr.getCurrentScene() != nullptr)
	// 	{
	// 		mgr.clearScene();
	// 		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 	}
	// 	else
	// 		glfwSetWindowShouldClose(window, true);
	// 	return;
	// }

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		createColorRect(window);

	cameraKeyMove(window);
}

void mainloop()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = (float)glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		loop(deltaTime);

		processInput();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	float width = 800, height = 600;
	if (!initGLFW(width, height))
	{
		glfwTerminate();
		return -1;
	}

	initCamera(width, height, 45.0f, 0.1f, 100.0f);

	mainloop();

	glfwTerminate();

	return 0;
}
