#include "MeshRenderer.h"
#include "gl_core_4_4.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void MeshRenderer::create_buffers()
{
	// generate vertex array object (vertex descriptor)
	glGenVertexArrays(1, &m_vao);

	//generate buffers
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	//positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4)); 
	//cleaning up
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshRenderer::initialize(std::vector<Vertex>& verts, std::vector<unsigned int>& indices)
{
	m_vertices.clear();
	m_indices.clear();

	for (auto v : verts)
		m_vertices.push_back(v);

	for (auto index : indices)
		m_indices.push_back(index);


	index_count = m_indices.size();
	vertex_count = m_vertices.size();

	this->create_buffers();
}

void MeshRenderer::draw(unsigned int mode)
{
	this->bind();
	if (mode == GL_TRIANGLE_STRIP)
	{
		glPrimitiveRestartIndex(0xFFFF);
		glEnable(GL_PRIMITIVE_RESTART);
	}

	glDrawElements(mode, this->index_count, GL_UNSIGNED_INT, 0);

	if (mode == GL_TRIANGLE_STRIP)
		glDisable(GL_PRIMITIVE_RESTART);

	this->unbind();
}

void MeshRenderer::bind()
{
	glBindVertexArray(this->m_vao);
}

void MeshRenderer::unbind()
{
	glBindVertexArray(0);
}

