
#include "RenderingGeometryApp.h"
#include <gl_core_4_4.h>
#include "Transform.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/ext.hpp"

class FileReader
{
public:
	std::string data;
	void ReadFromFile(std::string filename)
	{
		errno_t err;
		FILE* fp;
		err = fopen_s(&fp, filename.c_str(), "r");
		char buf[500];

		while (std::fgets(buf, sizeof buf, fp))
			data.append(buf);
		err = fclose(fp);
	}
};

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

	m_vertices =
	{//this was copied wrong -luke
		{ glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1) },
		{ glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1) },
		{ glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1) },
		{ glm::vec4(-10, -10, 0, 1), glm::vec4(1, 1, 1, 1) },
	};

	m_indices = std::vector<int>{ 0,1,2,2,3,0 };
	
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data() , GL_STATIC_DRAW);	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	
	FileReader* f = new FileReader();
	f->ReadFromFile("vertex.vert");
	const char* vsSource = f->data.c_str();

	const char* fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//specify where the source is located and bind to the specific shader handle
	glShaderSource(vertexShader, 1, (const char **)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

}

void RenderingGeometryApp::shutdown()
{
}

void RenderingGeometryApp::update(float dt)
{	
	view = glm::lookAt(glm::vec3(0,0,-20), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::quarter_pi<float>(), 16 / (float)9, 0.1f, 1000.f);
	model = glm::mat4(1);
}
 
void RenderingGeometryApp::draw()
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);

	int mvp = glGetUniformLocation(m_program, "ProjectionViewWorld");
	glm::mat4 pvm = projection * view * model;
	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(pvm));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);


}
