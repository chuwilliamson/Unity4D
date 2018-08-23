#pragma once
#include "Application.h"
#include <glm/glm/common.hpp>
#include <glm/glm/fwd.hpp>
#include <glm/glm/common.hpp>
#include <glm/glm/ext.hpp>
class IntroductionApp :
	public Application
{
public:
	IntroductionApp();
	~IntroductionApp();
	glm::mat4 model;
	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

