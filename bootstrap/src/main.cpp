#include <iostream>
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <glm/glm/fwd.hpp>
#include <glm/glm/common.hpp>
#include <glm/glm/ext.hpp>

#include <Gizmos.h>
//we need a base class to inherit from
//this baseclass will provide all the functionality we need to make seperate instances of our programs
//we will have a 1.IntroToOpenGL program
//-each program will have a class associated with it that will be used to draw
//we will have a 2.CamerasAndProjection program































//now let's get a window
//the window requires glfw
//glfw will be setup as follows
//SolutionDir/dep/include
//SolutionDir/dep/lib/glfw/x86
//SolutionDir/dep/lib/glfw/x64

//now let's get some math
//glm will be located at 
//SolutionDir/dep/include



GLFWwindow* window;
void DrawLines()
{
	glm::vec4 white = glm::vec4(1, 1, 1, 1);
	glm::vec4 black = glm::vec4(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		auto color = i == 10 ? white : black;
		auto p1 = glm::vec3(-10 + i, 0, 10);
		auto p2 = glm::vec3(-10 + i, 0, -10);

		auto p3 = glm::vec3(10, 0, -10 + i);
		auto p4 = glm::vec3(-10, 0, -10 + i);
		Gizmos::addLine(p1, p2, color);
		Gizmos::addLine(p3, p4, color);
	}
}
void Update()
{
	glm::mat4 model = glm::mat4(1);//model
	glm::mat4 model2 = glm::translate(model, glm::vec3(25, 20, 0));
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 25), glm::vec3(0), glm::vec3(0, 1, 0));//view
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);//projection

	//loop through the window
	bool lines = false;
	while (glfwWindowShouldClose(window) == false)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear frame buffer
		Gizmos::clear();		
		Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 10, 10, glm::vec4(.5, .25, .25, 1), &model);
		Gizmos::draw(projection * view);//draw
		Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 10, 10, glm::vec4(.5, .25, .25, 1), &model2);
		Gizmos::draw(projection * view);//draw
		glfwSwapBuffers(window);//swap the buffer for this window

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;


	}
}



int main()
{ 
	Update();
}