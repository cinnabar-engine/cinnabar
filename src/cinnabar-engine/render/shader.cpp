#include "shader.h"

#include <core/tpnt_log.h>
#include <iostream>
#include <managers/asset_manager.h>
#include <map>

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
		LOG_ERROR("SHADER_COMPILATION_ERROR of type: %s\n%s\n", type.c_str(), infoLog);
		exit(1);
	}
}
void checkCompileErrors(GLuint program) {
	int success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		LOG_ERROR("PROGRAM_LINKING_ERROR\n%s\n", infoLog);
		exit(1);
	}
}

GLuint createShader(GLenum type, std::string source) {
	const char* shaderSourceStr = source.c_str();
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSourceStr, NULL);
	glCompileShader(shader);

	checkCompileErrors(shader, type);
	return shader;
}

std::string setupShaderDefs(std::string source, std::map<std::string, std::string> options) {
	std::string shader = source;
	for (std::pair<std::string, std::string> option : options) {
		size_t defPos = shader.find("#define " + option.first);
		if (defPos == std::string::npos) {
			LOG_WARN("Invalid Option: %s", option.first.c_str());
			continue;
		}
		size_t defValuePos = defPos + option.first.length() + 9; // 8 is length of "#define " and space after name
		size_t lineEnd = shader.find('\n', defValuePos);
		if (lineEnd == std::string::npos)
			lineEnd = shader.length();

		shader = shader.replace(defValuePos, lineEnd - defValuePos, option.second);
	}
	return shader;
}


ce::Shader::Shader(std::string vertName, std::string geomName, std::string fragName, std::map<std::string, std::string> options)
	: m_program(glCreateProgram()) {
	ShaderFile shaderFile = ce::AssetManager::getShaderFiles(vertName, geomName, fragName);

	for (GLuint i = 0; i < m_attributes.size(); i++)
		glBindAttribLocation(m_program, i, (GLchar*)m_attributes[i].c_str());

	GLuint
		vertexShader = 0,
		fragmentShader = 0,
		geometryShader = 0;

	if (shaderFile.vertex != "")
		vertexShader = createShader(GL_VERTEX_SHADER, setupShaderDefs(shaderFile.vertex, options));
	if (shaderFile.fragment != "")
		fragmentShader = createShader(GL_FRAGMENT_SHADER, setupShaderDefs(shaderFile.fragment, options));
	if (shaderFile.geometry != "")
		geometryShader = createShader(GL_GEOMETRY_SHADER, setupShaderDefs(shaderFile.geometry, options));
	linkProgram(vertexShader, fragmentShader, vertexShader);
	GLint attrCount, uniformCount, customAttrCount;
	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attrCount);
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);
	customAttrCount = attrCount - m_attributes.size();
	if (customAttrCount > 0) {
		union {GLint size; GLenum type;} garbage;
		m_attributes.resize(attrCount);
		GLint nameMaxLen;
		glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameMaxLen);
		std::vector<GLchar> nameData(nameMaxLen);
		for (GLuint i = attrCount - customAttrCount; i < attrCount; i++) {
			GLsizei nameLen;
			glGetActiveAttrib(m_program, i, (GLsizei)nameMaxLen, &nameLen, &garbage.size, &garbage.type, nameData.data());
			m_attributes[i] = std::string((char*)nameData.data(), nameLen);
		}
	}
	if (uniformCount > m_uniforms.size()) {
		union {GLint size; GLenum type;} garbage;
		m_uniforms.resize(uniformCount);
		GLint nameMaxLen;
		glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameMaxLen);
		std::vector<GLchar> nameData(nameMaxLen);
		for (GLuint i = 0; i < uniformCount; i++) {
			GLsizei nameLen;
			glGetActiveUniform(m_program, i, (GLsizei)nameMaxLen, &nameLen, &garbage.size, &garbage.type, &nameData[0]);
			m_uniforms[i] = std::string((char*)nameData.data(), nameLen);
		}
	}
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

GLint ce::Shader::getAttribLocation(const std::string name) {
	std::vector<std::string>::iterator location = std::find(m_attributes.begin(), m_attributes.end(), name);
	if (location == m_attributes.end()) {
		LOG_WARN("Invalid Attribute: %s", name.c_str());
	}
	return std::distance(m_attributes.begin(), location);
}
GLint ce::Shader::getUniformLocation(const std::string name) {
	std::vector<std::string>::iterator location = std::find(m_uniforms.begin(), m_uniforms.end(), name);
	if (location == m_uniforms.end()) {
		LOG_WARN("Invalid Uniform: %s", name.c_str());
	}
	return std::distance(m_uniforms.begin(), location);
}

void ce::Shader::vertexAttribPointer(std::string attrib, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	GLint location = getAttribLocation(attrib);
	vertexAttribPointer((Attribute)location, size, type, normalized, stride, pointer);
}
void ce::Shader::vertexAttribPointer(Attribute location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	if ((GLint)location < Shader::MIN_LOC)
		return;
	glVertexAttribPointer((GLint)location, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray((GLint)location);
}


void ce::Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) {
	if (vertexShader != 0)
		glAttachShader(m_program, vertexShader);
	if (fragmentShader != 0)
		glAttachShader(m_program, fragmentShader);
	if (geometryShader != 0)
		glAttachShader(m_program, geometryShader);
	glLinkProgram(m_program);
	checkCompileErrors(m_program);
}
/*
GLint ce::Shader::registerAttribute(std::string name) {
	GLint location = glGetAttribLocation(m_program, name.c_str());
	if (location < Shader::MIN_LOC) {
		LOG_WARN("Invalid Attribute: %s", name.c_str());
	} else {
		m_attributes[location] = name;
		LOG_SUCCESS("Registered Attribute: %s", name.c_str());
	}
	return location;
}
GLint ce::Shader::registerUniform(std::string name) {
	GLint location = glGetUniformLocation(m_program, name.c_str());
	if (location < Shader::MIN_LOC) {
		LOG_WARN("Invalid Uniform: %s", name.c_str());
	} else {
		m_uniforms[location] = name;
		LOG_SUCCESS("Registered Uniform: %s", name.c_str());
	}
	return location;
}
*/
template <typename T>
void ce::Shader::setUniform(const std::string name, T value) {
	GLint location = getUniformLocation(name);
	if (location < Shader::MIN_LOC)
		return;
	setUniform(location, value);
}
template void ce::Shader::setUniform(const std::string, bool);
template void ce::Shader::setUniform(const std::string, int);
template void ce::Shader::setUniform(const std::string, float);
template void ce::Shader::setUniform(const std::string, glm::vec2);
template void ce::Shader::setUniform(const std::string, glm::vec3);
template void ce::Shader::setUniform(const std::string, glm::vec4);
template void ce::Shader::setUniform(const std::string, glm::mat2);
template void ce::Shader::setUniform(const std::string, glm::mat3);
template void ce::Shader::setUniform(const std::string, glm::mat4);
void ce::Shader::setUniform(const std::string name, float x, float y) {
	GLint location = getUniformLocation(name);
	if (location < Shader::MIN_LOC)
		return;
	setUniform(location, x, y);
}
void ce::Shader::setUniform(const std::string name, float x, float y, float z) {
	GLint location = getUniformLocation(name);
	if (location < Shader::MIN_LOC)
		return;
	setUniform(location, x, y, z);
}
void ce::Shader::setUniform(const std::string name, float x, float y, float z, float w) {
	GLint location = getUniformLocation(name);
	if (location < Shader::MIN_LOC)
		return;
	setUniform(location, x, y, z, w);
}

void ce::Shader::setUniform(GLint location, bool value) {
	bind();
	glUniform1i(location, (int)value);
	unbind();
}
void ce::Shader::setUniform(GLint location, int value) {
	bind();
	glUniform1i(location, value);
	unbind();
}
void ce::Shader::setUniform(GLint location, float value) {
	bind();
	glUniform1f(location, value);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::vec2 value) {
	bind();
	glUniform2fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::vec3 value) {
	bind();
	glUniform3fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::vec4 value) {
	bind();
	glUniform4fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::mat2 mat) {
	bind();
	glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::mat3 mat) {
	bind();
	glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
}
void ce::Shader::setUniform(GLint location, glm::mat4 mat) {
	bind();
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	unbind();
}

void ce::Shader::setUniform(GLint location, float x, float y) {
	bind();
	glUniform2f(location, x, y);
	unbind();
}
void ce::Shader::setUniform(GLint location, float x, float y, float z) {
	bind();
	glUniform3f(location, x, y, z);
	unbind();
}
void ce::Shader::setUniform(GLint location, float x, float y, float z, float w) {
	bind();
	glUniform4f(location, x, y, z, w);
	unbind();
}
