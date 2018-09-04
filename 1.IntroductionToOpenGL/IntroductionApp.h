#pragma once
#define GLM_FORCE_SWIZZLE
#include "Application.h"


struct Transform;

class IntroductionApp :	public Application
{
public:
	IntroductionApp();
	~IntroductionApp();
	Transform* modelTransform;
	glm::mat4 model;
	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};

