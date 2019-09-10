#pragma once
#include <Application.h>
#include <vector>
#include <glm/glm/glm.hpp>

class RenderingGeometryApp : public Application
{
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 color;
	};

	RenderingGeometryApp();
	~RenderingGeometryApp();

	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_VBO;
	unsigned int m_program;

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;
	std::vector<Vertex> m_floor;


	// Inherited via Application
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float dt) override;
	virtual void draw() override;

	// Inherited via Application
	virtual void OnGUI() override;
};

