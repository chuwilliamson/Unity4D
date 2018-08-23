#define GLM_FORCE_SWIZZLE
#include "IntroductionApp.h"

#include <iostream>
#include <Gizmos.h>

IntroductionApp::IntroductionApp(): model(1)
{
}


IntroductionApp::~IntroductionApp()
{
}

void IntroductionApp::startup()
{
	Gizmos::create();
}

void IntroductionApp::shutdown()
{
	Gizmos::destroy();
}

void IntroductionApp::update(float dt)
{
	model = glm::translate(model, glm::vec3(glm::cos(dt), 0, 0));
}

void IntroductionApp::draw()
{
	
	
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 25), glm::vec3(0), glm::vec3(0, 1, 0));//view
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);//projection

																							  //loop through the window
	bool lines = false;
	Gizmos::clear();
	Gizmos::addSphere(model[3].xyz(), 5, 10, 10, glm::vec4(.5, .25, .25, 1), &model);
	Gizmos::draw(projection * view);//draw
	 

}
