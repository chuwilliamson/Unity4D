#include "Shader.h"
#include <stdio.h>
#include "gl_core_4_4.h"


Shader::Shader() : program(m_program)
{
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
}


Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

bool Shader::load(const char* filename, unsigned int type, bool isFile/* = true*/)
{
	char* data;
	if (isFile)
	{
		FILE* fp;
		errno_t success = fopen_s(&fp, filename, "rb");
		if (success < 0)
			perror("no file");
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		data = new char[size + 1];
		fread_s(data, size, sizeof(char), size, fp);
		data[size] = '\0';
		fclose(fp);
	}
	else
	{
		data = (char*)filename;
	}

	const char* src = data;
	int success = GL_FALSE;

	switch (type) {
	case GL_VERTEX_SHADER:
		//try compile
		glShaderSource(m_vertexShader, 1, (const char **)&data, 0);
		glCompileShader(m_vertexShader);
		glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE && isFile)
			return false;
		vsSource = src;
		break;

	case GL_FRAGMENT_SHADER:

		glShaderSource(m_fragmentShader, 1, (const char**)&data, 0);
		glCompileShader(m_fragmentShader);
		glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE && isFile)
			return false;
		fsSource = src;
		break;
	}
	return true;
}

bool Shader::attach()
{
	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
		m_program = glCreateProgram();

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
#if DEBUG
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
	}
#endif 

	return true;
}

void Shader::defaultLoad()
{
	vsSource = "#version 410\n \
                            layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vec4(.25, .25, .25, 0); }";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//specify where the source is located and bind to the specific shader handle
	glShaderSource(vertexShader, 1, (const char **)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
		m_program = glCreateProgram();

	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);


	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

}

unsigned int Shader::getUniform(const char * name)
{
	return glGetUniformLocation(m_program, name);
}

bool Shader::bindUniform(const char* name, int value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform1i(i, value);
	return true;
}

bool Shader::bindUniform(const char* name, float value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform1f(i, value);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::vec2& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform2f(i, value.x, value.y);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::vec3& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform3f(i, value.x, value.y, value.z);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::vec4& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform4f(i, value.x, value.y, value.z, value.w);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::mat2& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix2fv(i, 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::mat3& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix3fv(i, 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::bindUniform(const char* name, const glm::mat4& value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix4fv(i, 1, GL_FALSE, &value[0][0]);
	return true;
}

bool Shader::bindUniform(const char* name, int count, int* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform1iv(i, count, value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, float* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform1fv(i, count, value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::vec2* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform2fv(i, count, (float*)value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::vec3* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform3fv(i, count, (float*)value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::vec4* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniform4fv(i, count, (float*)value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::mat2* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix2fv(i, count, GL_FALSE, (float*)value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::mat3* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix3fv(i, count, GL_FALSE, (float*)value);
	return true;
}

bool Shader::bindUniform(const char* name, int count, const glm::mat4* value) {
	assert(m_program > 0 && "Invalid shader program");
	int i = glGetUniformLocation(m_program, name);
	if (i < 0) {
		//printf("Shader uniform [%s] not found! Is it being used?\n", name);
		return false;
	}
	glUniformMatrix4fv(i, count, GL_FALSE, (float*)value);
	return true;
}

void Shader::bindUniform(int ID, int value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform1i(ID, value);
}

void Shader::bindUniform(int ID, float value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform1f(ID, value);
}

void Shader::bindUniform(int ID, const glm::vec2& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform2f(ID, value.x, value.y);
}

void Shader::bindUniform(int ID, const glm::vec3& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform3f(ID, value.x, value.y, value.z);
}

void Shader::bindUniform(int ID, const glm::vec4& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform4f(ID, value.x, value.y, value.z, value.w);
}

void Shader::bindUniform(int ID, const glm::mat2& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix2fv(ID, 1, GL_FALSE, &value[0][0]);
}

void Shader::bindUniform(int ID, const glm::mat3& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix3fv(ID, 1, GL_FALSE, &value[0][0]);
}

void Shader::bindUniform(int ID, const glm::mat4& value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix4fv(ID, 1, GL_FALSE, &value[0][0]);
}

void Shader::bindUniform(int ID, int count, int* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform1iv(ID, count, value);
}

void Shader::bindUniform(int ID, int count, float* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform1fv(ID, count, value);
}

void Shader::bindUniform(int ID, int count, const glm::vec2* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform2fv(ID, count, (float*)value);
}

void Shader::bindUniform(int ID, int count, const glm::vec3* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform3fv(ID, count, (float*)value);
}

void Shader::bindUniform(int ID, int count, const glm::vec4* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniform4fv(ID, count, (float*)value);
}

void Shader::bindUniform(int ID, int count, const glm::mat2* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix2fv(ID, count, GL_FALSE, (float*)value);
}

void Shader::bindUniform(int ID, int count, const glm::mat3* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix3fv(ID, count, GL_FALSE, (float*)value);
}

void Shader::bindUniform(int ID, int count, const glm::mat4* value) {
	assert(m_program > 0 && "Invalid shader program");
	assert(ID >= 0 && "Invalid shader uniform");
	glUniformMatrix4fv(ID, count, GL_FALSE, (float*)value);
}