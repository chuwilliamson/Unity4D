
#include "RenderingGeometryApp.h"
#include <gl_core_4_4.h>
#include "Transform.h"
#include "glm/glm/glm.hpp"
#include "MeshRenderer.h"
#include "Shader.h"

RenderingGeometryApp::RenderingGeometryApp()
{
}

RenderingGeometryApp::~RenderingGeometryApp()
{
}

void RenderingGeometryApp::startup()
{
	// A----B
	// |\	|
	// | \	|
	// |  \ |
	//D|---\|C
	shader = new Shader();
	shader->load("vertex.vert", GL_VERTEX_SHADER);
	shader->load("fragment.frag", GL_FRAGMENT_SHADER); 
	shader->attach();
	mesh = new MeshRenderer();
	std::vector<MeshRenderer::Vertex> cube_verts = std::vector<MeshRenderer::Vertex>
	{
		// front
		{   glm::vec4(-1.0, -1.0,  1.0, 1.0), glm::vec4(1, 0, 0, 1) },
		{   glm::vec4(1.0,  -1.0,  1.0, 1.0), glm::vec4(0, 1, 0, 1) },
		{   glm::vec4(1.0,   1.0,  1.0, 1.0), glm::vec4(0, 0, 1, 1) },
		{	glm::vec4(-1.0,  1.0,  1.0, 1.0), glm::vec4(1, 0, 0, 1) },
		// back
		{	glm::vec4(-1.0, -1.0, -1.0, 1.0), glm::vec4(1, 0, 0, 1) },
		{	glm::vec4(1.0,  -1.0, -1.0, 1.0), glm::vec4(0, 1, 0, 1) },
		{	glm::vec4(1.0,   1.0, -1.0, 1.0), glm::vec4(1, 0, 1, 1) },
		{	glm::vec4(-1.0,  1.0, -1.0, 1.0), glm::vec4(1, 0, 0, 1) }
	};

	std::vector<unsigned int> cube_indices = std::vector<unsigned int>
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};

	std::vector<MeshRenderer::Vertex> verts = std::vector<MeshRenderer::Vertex>
	{//this was copied wrong -luke
		{ glm::vec4(-10,  10, 0, 1),  glm::vec4(1, 0, 0, 1) },
		{ glm::vec4( 10,  10, 0, 1),  glm::vec4(0, 1, 0, 1) },
		{ glm::vec4( 10, -10, 0, 1),  glm::vec4(0, 0, 1, 1) },
		{ glm::vec4(-10, -10, 0, 1),  glm::vec4(1, 1, 1, 1) },
	};

	std::vector<unsigned int> m_indices = std::vector<unsigned int>{ 0, 1, 2, 2, 3, 0 };

	mesh->initialize(cube_verts, cube_indices);
}

void RenderingGeometryApp::update(float dt)
{
	view = glm::lookAt(glm::vec3(5, 5, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::quarter_pi<float>(), 16 / (float)9, 0.1f, 1000.f);
	
	model = glm::mat4(1);
}

void RenderingGeometryApp::draw()
{
	glm::mat4 pvm = projection * view * model;
	shader->bind();
	shader->bindUniform("ProjectionViewWorld", pvm);
	mesh->draw(GL_TRIANGLES);
	shader->unbind();
}
void RenderingGeometryApp::shutdown()
{
}