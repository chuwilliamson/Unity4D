#pragma once
#include <glm/glm/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();
	void bind();
	void unbind();
	bool load(const char * filename, unsigned int type, bool isFile = true);
	bool attach();
	void defaultLoad();
	//void load();
	unsigned int getUniform(const char *);
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	const char* vsSource;
	const char* fsSource;
	void bindUniform(int ID, int value);
	void bindUniform(int ID, float value);
	void bindUniform(int ID, const glm::vec2& value);
	void bindUniform(int ID, const glm::vec3& value);
	void bindUniform(int ID, const glm::vec4& value);
	void bindUniform(int ID, const glm::mat2& value);
	void bindUniform(int ID, const glm::mat3& value);
	void bindUniform(int ID, const glm::mat4& value);
	void bindUniform(int ID, int count, int* value);
	void bindUniform(int ID, int count, float* value);
	void bindUniform(int ID, int count, const glm::vec2* value);
	void bindUniform(int ID, int count, const glm::vec3* value);
	void bindUniform(int ID, int count, const glm::vec4* value);
	void bindUniform(int ID, int count, const glm::mat2* value);
	void bindUniform(int ID, int count, const glm::mat3* value);
	void bindUniform(int ID, int count, const glm::mat4* value);

	// these calls should be avoided, but wraps up opengl a little
	bool bindUniform(const char* name, int value);
	bool bindUniform(const char* name, float value);
	bool bindUniform(const char* name, const glm::vec2& value);
	bool bindUniform(const char* name, const glm::vec3& value);
	bool bindUniform(const char* name, const glm::vec4& value);
	bool bindUniform(const char* name, const glm::mat2& value);
	bool bindUniform(const char* name, const glm::mat3& value);
	bool bindUniform(const char* name, const glm::mat4& value);
	bool bindUniform(const char* name, int count, int* value);
	bool bindUniform(const char* name, int count, float* value);
	bool bindUniform(const char* name, int count, const glm::vec2* value);
	bool bindUniform(const char* name, int count, const glm::vec3* value);
	bool bindUniform(const char* name, int count, const glm::vec4* value);
	bool bindUniform(const char* name, int count, const glm::mat2* value);
	bool bindUniform(const char* name, int count, const glm::mat3* value);
	bool bindUniform(const char* name, int count, const glm::mat4* value);
	unsigned int& program;

private:
	unsigned int m_program;
};


struct ShaderData {
	Shader* shader;
	char* source;
	unsigned type;
	bool isFile;
};