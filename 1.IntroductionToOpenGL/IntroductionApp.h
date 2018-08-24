#pragma once
#define GLM_FORCE_SWIZZLE
#include "Application.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/fwd.hpp>
#include "Transform.h"

class IntroductionApp :	public Application
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

