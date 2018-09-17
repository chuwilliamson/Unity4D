#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application() :
	m_window(nullptr),
	m_gameover(false),
	m_clearColor{ 1,1,1,1 },
	m_runningTime(0)
{}

Application::~Application()
{
}

void Application::run(const char * title, unsigned int width,
	unsigned int height, bool fullscreen)
{
	glfwInit(); //initialize glfw	
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);//make window
	glfwMakeContextCurrent(m_window);//make the current window our opengl target
	auto success = ogl_LoadFunctions();//initializes openGL

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::printf("major:: %i.%i", major, minor);

	glClearColor(.8f, .8f, 0.8f, 1);//sets the clear color for the window
	glEnable(GL_DEPTH_TEST); // enables the depth buffer 
	startup();

	while (!m_gameover)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear frame buffer	

		glfwPollEvents();
		update(glfwGetTime());

		draw();

		glfwSwapBuffers(m_window);//swap the buffer for this window
		m_gameover = glfwGetKey(m_window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(m_window);
	}
	shutdown();
}

void Application::clearScreen()
{
}
