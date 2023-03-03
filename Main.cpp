#include "DrawSquare.h"

#define S_WIDTH 1200
#define S_HEIGHT 1200



int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(S_WIDTH, S_HEIGHT, "Main Window", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create Window." << std::endl;
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, S_WIDTH, S_HEIGHT);

	NumberOfSquares(2);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawSquare(Point(-0.5f, -0.5f, Color(0.0f, 0.0f, 0.4f)), 0.30f);
		DrawSquare(Point(0.5f, 0.5f, Color(0.2f, 0.3f, 0.4f)), 0.30f);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}