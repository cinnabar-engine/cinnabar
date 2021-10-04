#include <cinnabar-render/shader.hpp>

#include <iostream>
#include <map>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cinnabar-core/tpnt_log.h>

#include <cinnabar-render/types.hpp>
#include <cinnabar-render/asset_manager.hpp>

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

glm::uint32 createShader(GLenum type, std::string source) {
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

	ShaderFile shaderFile = ce::assetManager::getShaderFile(vertName, geomName, fragName);

	for (GLuint i = 0; i < m_attributes.size(); i++)
		glBindAttribLocation(m_program, i, (GLchar*)m_attributes[i].c_str());

	GLuint
		vertexShader = 0,
		fragmentShader = 0,
		geometryShader = 0;

	if (shaderFile.vert != "")
		vertexShader = createShader(GL_VERTEX_SHADER, setupShaderDefs(shaderFile.vert, options));
	if (shaderFile.frag != "")
		fragmentShader = createShader(GL_FRAGMENT_SHADER, setupShaderDefs(shaderFile.frag, options));
	if (shaderFile.geom != "")
		geometryShader = createShader(GL_GEOMETRY_SHADER, setupShaderDefs(shaderFile.geom, options));
	linkProgram(vertexShader, fragmentShader, geometryShader);


	GLint attrCount, uniformCount, customAttrCount;
	glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &attrCount);
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &uniformCount);

	customAttrCount = attrCount - m_attributes.size();
	if (customAttrCount > 0) {
		GLint size;
		GLenum type;
		m_attributes.reserve(attrCount);
		GLint nameMaxLen;
		glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameMaxLen);
		std::vector<GLchar> nameData(nameMaxLen);
		for (GLuint i = attrCount - customAttrCount; i < attrCount;) {
			GLsizei nameLen;
			glGetActiveAttrib(m_program, i, (GLsizei)nameMaxLen, &nameLen, &size, &type, nameData.data());

			m_attributes.push_back(std::string((char*)nameData.data(), nameLen)); // push first item
			i++;
			if (size > 1) { // push extra items if array
				std::string nameString = std::string((char*)nameData.data(), nameLen - 2); // stores "varname["
				for (GLint j = 1; j < size; j++) {
					m_uniforms.push_back(nameString + std::to_string(j) + std::string("]"));
					i++;
				}
			}
		}
	}
	if (uniformCount > m_uniforms.size()) {
		GLint size;
		GLenum type;
		m_uniforms.reserve(uniformCount);
		GLint nameMaxLen;
		glGetProgramiv(m_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameMaxLen);
		std::vector<GLchar> nameData(nameMaxLen);
		for (GLuint i = 0; i < uniformCount;) {
			GLsizei nameLen;
			glGetActiveUniform(m_program, i, (GLsizei)nameMaxLen, &nameLen, &size, &type, &nameData[0]);

			m_uniforms.push_back(std::string((char*)nameData.data(), nameLen)); // push first item
			i++;
			if (size > 1) { // push extra items if array
				std::string nameString = std::string((char*)nameData.data(), nameLen - 2); // stores "varname["
				for (GLint j = 1; j < size; j++) {
					m_uniforms.push_back(nameString + std::to_string(j) + std::string("]"));
					i++;
				}
			}
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

glm::uint32 ce::Shader::getShader() {
	return m_program;
}

glm::int32 ce::Shader::getAttribLocation(const std::string name) {
	std::vector<std::string>::iterator location = std::find(m_attributes.begin(), m_attributes.end(), name);
	if (location == m_attributes.end()) {
		LOG_WARN("Invalid Attribute: %s", name.c_str());
	}
	return std::distance(m_attributes.begin(), location);
}
glm::int32 ce::Shader::getUniformLocation(const std::string name) {
	std::vector<std::string>::iterator location = std::find(m_uniforms.begin(), m_uniforms.end(), name);
	if (location == m_uniforms.end()) {
		LOG_WARN("Invalid Uniform: %s", name.c_str());
		return -1;
	}
	return std::distance(m_uniforms.begin(), location);
}

void ce::Shader::vertexAttribPointer(std::string attrib, glm::int32 size, Datatype type, bool normalized, glm::uint32 stride, const void* pointer) {
	GLint location = getAttribLocation(attrib);
	vertexAttribPointer((Attribute)location, (GLint)size, (GLenum)type, (GLboolean)normalized, (GLsizei)stride, pointer);
}
void ce::Shader::vertexAttribPointer(Attribute location, glm::int32 size, Datatype type, bool normalized, glm::uint32 stride, const void* pointer) {
	if ((GLint)location < 0)
		return;
	glVertexAttribPointer((GLint)location, (GLint)size, (GLenum)type, (GLboolean)normalized, (GLsizei)stride, pointer);
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
glm::int32 ce::Shader::registerAttribute(std::string name) {
	GLint location = glGetAttribLocation(m_program, name.c_str());
	if (location < 0) {
		LOG_WARN("Invalid Attribute: %s", name.c_str());
	} else {
		m_attributes[location] = name;
		LOG_SUCCESS("Registered Attribute: %s", name.c_str());
	}
	return location;
}
glm::int32 ce::Shader::registerUniform(std::string name) {
	GLint location = glGetUniformLocation(m_program, name.c_str());
	if (location < 0) {
		LOG_WARN("Invalid Uniform: %s", name.c_str());
	} else {
		m_uniforms[location] = name;
		LOG_SUCCESS("Registered Uniform: %s", name.c_str());
	}
	return location;
}
*/
template <typename T>
glm::int32 ce::Shader::setUniformArray(const std::string name, glm::uint32 count, const T* value) {
	glm::int32 location = getUniformLocation(name);
	if (location >= 0)
		setUniformArray(location, count, value);
	return location;
}
template <typename T>
glm::int32 ce::Shader::setUniform(const std::string name, const T& value) {
	glm::int32 location = getUniformLocation(name);
	if (location >= 0)
		setUniform(location, value);
	return location;
}
template <typename T>
void ce::Shader::setUniform(glm::int32 location, const T& value) {
	setUniformArray(location, 1, &value);
}
template glm::int32 ce::Shader::setUniform(const std::string, const bool&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::bvec2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::bvec3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::bvec4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::int32&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::ivec2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::ivec3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::ivec4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::uint32&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::uvec2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::uvec3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::uvec4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::float32&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::vec2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::vec3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::vec4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::float64&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::dvec2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::dvec3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::dvec4&);

template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat2x3&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat3x2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat2x4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat4x2&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat3x4&);
template glm::int32 ce::Shader::setUniform(const std::string, const glm::mat4x3&);
glm::int32 ce::Shader::setUniform(const std::string name, float x, float y) {
	GLint location = getUniformLocation(name);
	if (location >= 0)
		setUniform(location, x, y);
	return location;
}
glm::int32 ce::Shader::setUniform(const std::string name, float x, float y, float z) {
	GLint location = getUniformLocation(name);
	if (location >= 0)
		setUniform(location, x, y, z);
	return location;
}
glm::int32 ce::Shader::setUniform(const std::string name, float x, float y, float z, float w) {
	GLint location = getUniformLocation(name);
	if (location >= 0)
		setUniform(location, x, y, z, w);
	return location;
}

#define SHADER_GENERATOR(TYPE, SUFFIX, ...) \
	template <> \
	void ce::Shader::setUniformArray<TYPE>(glm::int32 location, glm::uint32 count, const TYPE* value) { \
		bind(); \
		glUniform##SUFFIX(location, count, __VA_ARGS__); \
		unbind(); \
	}

SHADER_GENERATOR(bool, 1iv, (GLint*)value)
SHADER_GENERATOR(glm::bvec2, 2iv, (GLint*)value)
SHADER_GENERATOR(glm::bvec3, 3iv, (GLint*)value)
SHADER_GENERATOR(glm::bvec4, 4iv, (GLint*)value)
SHADER_GENERATOR(glm::int32, 1iv, value)
SHADER_GENERATOR(glm::ivec2, 2iv, (GLint*)value)
SHADER_GENERATOR(glm::ivec3, 3iv, (GLint*)value)
SHADER_GENERATOR(glm::ivec4, 4iv, (GLint*)value)
SHADER_GENERATOR(glm::uint32, 1uiv, value)
SHADER_GENERATOR(glm::uvec2, 2uiv, (GLuint*)value)
SHADER_GENERATOR(glm::uvec3, 3uiv, (GLuint*)value)
SHADER_GENERATOR(glm::uvec4, 4uiv, (GLuint*)value)
SHADER_GENERATOR(glm::float32, 1fv, value)
SHADER_GENERATOR(glm::vec2, 2fv, (GLfloat*)value)
SHADER_GENERATOR(glm::vec3, 3fv, (GLfloat*)value)
SHADER_GENERATOR(glm::vec4, 4fv, (GLfloat*)value)
SHADER_GENERATOR(glm::float64, 1dv, value)
SHADER_GENERATOR(glm::dvec2, 2dv, (GLdouble*)value)
SHADER_GENERATOR(glm::dvec3, 3dv, (GLdouble*)value)
SHADER_GENERATOR(glm::dvec4, 4dv, (GLdouble*)value)

SHADER_GENERATOR(glm::mat2, Matrix2fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat3, Matrix3fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat4, Matrix4fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat2x3, Matrix2x3fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat3x2, Matrix3x2fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat2x4, Matrix2x4fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat4x2, Matrix4x2fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat3x4, Matrix3x4fv, GL_FALSE, (GLfloat*)value)
SHADER_GENERATOR(glm::mat4x3, Matrix4x3fv, GL_FALSE, (GLfloat*)value)

#undef SHADER_GENERATOR

void ce::Shader::setUniform(glm::int32 location, float x, float y) {
	bind();
	glUniform2f(location, x, y);
	unbind();
}
void ce::Shader::setUniform(glm::int32 location, float x, float y, float z) {
	bind();
	glUniform3f(location, x, y, z);
	unbind();
}
void ce::Shader::setUniform(glm::int32 location, float x, float y, float z, float w) {
	bind();
	glUniform4f(location, x, y, z, w);
	unbind();
}
