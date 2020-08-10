#include "main.h"
#include "camera.h"
#include "scenecontroller.h"

GLFWwindow *window = NULL;

bool initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Create window failed" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scrollCallback);

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		createColorRect();

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
	if (!initGLFW())
	{
		glfwTerminate();
		return -1;
	}

	initCamera();

	mainloop();

	glfwTerminate();

	return 0;
}
