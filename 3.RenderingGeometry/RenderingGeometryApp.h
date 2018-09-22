#pragma once
#define GLM_FORCE_SWIZZLE
#include "Application.h"
#include <vector>
#include <glm/glm/glm.hpp>

class MeshRenderer;
class Shader;
class Transform;

class RenderingGeometryApp :public Application
{
public:

	RenderingGeometryApp(); 
	Shader* shader;
	MeshRenderer* mesh;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	~RenderingGeometryApp();

	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;

};

