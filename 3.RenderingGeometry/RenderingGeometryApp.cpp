#define GLM_FORCE_SWIZZLE
#include "RenderingGeometryApp.h"
#include <gl_core_4_4.h>
#include <glm/glm/ext.hpp>
#include "imgui.h"
RenderingGeometryApp::RenderingGeometryApp()
{
	m_model = glm::mat4(1);
}

RenderingGeometryApp::~RenderingGeometryApp() {}

void RenderingGeometryApp::startup()
{
	//gen
	//bind
	//use somehow
	//unbind
	//A----B
	//\
	// \
	//  \
	//   \
	//D----C
	//Begin Mesh class
	//Mesh.cpp

	Vertex A = {
		glm::vec4(-10,10,0,1),
		glm::vec4(1,0,0,1)
	};

	Vertex B = {
		glm::vec4(10,10,0,1),
		glm::vec4(0,1,0,1)
	};

	Vertex C = { glm::vec4(10,-10,0,1), glm::vec4(0,0,1,1) };
	Vertex D = { glm::vec4(-10,-10,0,1), glm::vec4(0,0,0,1) };

	m_vertices = { A,B,C,D };
	m_indices = { 0,1,2,2,3,0 };

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		m_indices.size() * sizeof(unsigned int),
		m_indices.data(),
		GL_STATIC_DRAW);

	//all the data is on the card
	//now we need to describe the individual items

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//describe the next item which is color
	glEnableVertexAttribArray(1);
	//|position|color|
	//                <---starts here sizeof(Vertex)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//====END BUFFERING====//
	//Shader.cpp
	//we have bound everything now time for the shader setup
	const char*	vsSource = "#version 410\n \
                            layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	const char *fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";

	//make a handle for the vertex shader
	//this handle is used to be linked to the shader program
	//WE ARE DEFINING THE SHADER PIPELINE
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//specify the code that we are going to compile
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);

	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);
	//make a handle for the program
	m_program = glCreateProgram();
	//link the shader programs to that program
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
}

void RenderingGeometryApp::shutdown()
{
}

void RenderingGeometryApp::update(float dt)
{

	glm::vec3 eye = glm::vec3(0, -10, -30);
	m_view = glm::lookAt(eye, glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
}

void RenderingGeometryApp::draw()
{
	glBindVertexArray(m_VAO);
	glUseProgram(m_program);
	//get an id that is the variable from the shader
	int variableId = glGetUniformLocation(m_program, "ProjectionViewWorld");
	//create a variable to send
	glm::mat4 mvp = m_projection * m_view * m_model;
	//send the variable
	glUniformMatrix4fv(variableId, 1, GL_FALSE, &mvp[0][0]);
	//set the draw mode to render the front and back of our geometry
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindVertexArray(0);
}

void RenderingGeometryApp::OnGUI()
{
	float pos[4] = { m_model[3].x, m_model[3].y, m_model[3].z, 1 };
	if (ImGui::SliderFloat4("pos", pos, -10, 10))
	{
		m_model[3].xyz = glm::vec3(pos[0], pos[1], pos[2]);
	}
}
