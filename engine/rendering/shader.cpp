#include "shader.h"
#include <core/tpnt_log.h>
#include <iostream>
#include <managers/asset_manager.h>

void checkCompileErrors(GLuint shader, GLint shaderType) {
	std::string type;
	switch (shaderType) {
		case GL_VERTEX_SHADER:
			type = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			type = "FRAGMENT";
			break;
		case GL_GEOMETRY_SHADER:
			type = "GEOMETRY";
			break;
		default:
			return;
	}
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		LOG_ERROR(
			"SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n");
		exit(-1);
	}
}

void checkCompileErrors(GLuint program) {
	int success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		LOG_ERROR("PROGRAM_LINKING_ERROR\n" + infoLog + "\n");
		exit(-1);
	}
}

int createShader(GLenum type, std::string source) {
	const char* shaderSourceStr = source.c_str();
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSourceStr, NULL);
	glCompileShader(shader);

	checkCompileErrors(shader, type);
	return shader;
}

void ce::Shader::linkProgram(
	int vertexShader, int fragmentShader, int geometryShader) {
	if (vertexShader != 0)
		glAttachShader(m_program, vertexShader);
	if (fragmentShader != 0)
		glAttachShader(m_program, fragmentShader);
	if (geometryShader != 0)
		glAttachShader(m_program, geometryShader);
	glLinkProgram(m_program);
	checkCompileErrors(m_program);
}

int ce::Shader::registerAttribute(std::string name) {
	int location = glGetAttribLocation(m_program, name.c_str());
	if (location < Shader::MIN_LOC) {
		LOG_ERROR("Invalid Attribute: " + name);
		return MIN_LOC - 1;
	}
	m_attributes.insert(m_attributes.begin() + location, name);
	LOG_SUCCESS("Registered Attribute: " + name);
	return location;
}

int ce::Shader::registerUniform(std::string name) {
	int location = glGetUniformLocation(m_program, name.c_str());
	if (location < Shader::MIN_LOC) {
		LOG_ERROR("Invalid Uniform: " + name);
		return MIN_LOC - 1;
	}
	m_uniforms.insert(m_uniforms.begin() + location, name);
	LOG_SUCCESS("Registered Uniform: " + name);
	return location;
}

ce::Shader::Shader(const char* name)
	: m_program(glCreateProgram()) {
	ShaderFile shaderFile = ce::AssetManager::getShaderFile(name);

	int vertexShader = 0;
	int fragmentShader = 0;
	int geometryShader = 0;

	if (shaderFile.vertex != "")
		vertexShader = createShader(GL_VERTEX_SHADER, shaderFile.vertex);
	if (shaderFile.fragment != "")
		fragmentShader = createShader(GL_FRAGMENT_SHADER, shaderFile.fragment);
	if (shaderFile.geometry != "")
		geometryShader = createShader(GL_GEOMETRY_SHADER, shaderFile.geometry);
	linkProgram(vertexShader, fragmentShader, vertexShader);

	int attrCount = 0, uniformCount = 0;
	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attrCount);
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);

	m_attributes.resize(attrCount);
	m_uniforms.resize(uniformCount);
}

ce::Shader::~Shader() {
	glDeleteProgram(m_program);
}

void ce::Shader::bind() {
	glUseProgram(m_program);
}

void ce::Shader::unbind() {
	glUseProgram(0);
}

GLuint ce::Shader::getShader() {
	return m_program;
}

GLuint ce::Shader::getAttribLocation(const std::string name) {
	if (m_attributes.size() < (size_t)Shader::MIN_LOC)
		return registerAttribute(name.c_str());
	auto location = std::find(m_attributes.begin(), m_attributes.end(), name);
	if (location != m_attributes.end())
		return std::distance(m_attributes.begin(), location);
	else
		return registerAttribute(name.c_str());
}

GLuint ce::Shader::getUniformLocation(const std::string name) {
	if (m_attributes.size() < (size_t)Shader::MIN_LOC)
		return registerUniform(name.c_str());
	auto location = std::find(m_uniforms.begin(), m_uniforms.end(), name);
	if (location != m_uniforms.end())
		return std::distance(m_uniforms.begin(), location);
	else
		return registerUniform(name.c_str());
}

void ce::Shader::vertexAttribPointer(std::string attrib, GLint size,
	GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	GLuint location = getAttribLocation(attrib);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glVertexAttribPointer(location, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(location);
}

void ce::Shader::setBool(const std::string name, bool value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform1i(location, (int)value);
	unbind();
}

void ce::Shader::setInt(const std::string name, int value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform1i(location, value);
	unbind();
}

void ce::Shader::setFloat(const std::string name, float value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform1f(location, value);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setVec2(const std::string name, vec2 value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform2fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setVec2(const std::string name, float x, float y) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform2f(location, x, y);
	// storageLog("uniform", name, &x, &y);
	unbind();
}
void ce::Shader::setVec3(const std::string name, vec3 value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform3fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setVec3(const std::string name, float x, float y, float z) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform3f(location, x, y, z);
	// storageLog("uniform", name, &x, &y, &z);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setVec4(const std::string name, vec4 value) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform4fv(location, 1, &value[0]);
	// storageLog("uniform", name, &value[0]);
	unbind();
}
void ce::Shader::setVec4(
	const std::string name, float x, float y, float z, float w) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniform4f(location, x, y, z, w);
	// storageLog("uniform", name, &x, &y, &z, &w);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat2(const std::string name, mat2 mat) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
	// storageLog("uniform", name, &mat[0][0]);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat3(const std::string name, mat3 mat) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	// storageLog("uniform", name, &mat[0][0]);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat4(const std::string name, mat4 mat) {
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC)
		return;
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	// storageLog("uniform", name, &mat[0][0]);
	unbind();
}
