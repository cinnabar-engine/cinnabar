#include "shader.h"

void checkCompileErrors(ce::Logger* logger, GLuint shader, GLint shaderType)
{
	std::string type;
	switch (shaderType)
	{
	case GL_VERTEX_SHADER: type = "VERTEX"; break;
	case GL_FRAGMENT_SHADER: type = "FRAGMENT"; break;
	case GL_GEOMETRY_SHADER: type = "GEOMETRY"; break;
	default: return;
	}
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		logger->Error("SHADER_COMPILATION_ERROR of type: " + type + "\n" + std::string(infoLog) + "\n-------------------------------------------------------");
	}
}

void checkCompileErrors(ce::Logger* logger, GLuint program)
{
	int success;
	char infoLog[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		logger->Error("PROGRAM_LINKING_ERROR\n" + std::string(&infoLog[0]) + "\n-------------------------------------------------------");
	}
}

int createShader(ce::Logger* logger, GLenum type, std::string source)
{
	const char* shaderSourceStr = source.c_str();
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSourceStr, NULL);
	glCompileShader(shader);

	checkCompileErrors(logger, shader, type);
	return shader;
}

ce::Logger* ce::Shader::GetLogger() {
	return new Logger("shader");
}

void ce::Shader::linkProgram(int vertexShader, int fragmentShader, int geometryShader) {
	if (vertexShader != 0) glAttachShader(program, vertexShader);
	if (fragmentShader != 0) glAttachShader(program, fragmentShader);
	if (geometryShader != 0) glAttachShader(program, geometryShader);
	glLinkProgram(program);
	checkCompileErrors(GetLogger(), program);
}

int ce::Shader::registerAttribute(std::string name)
{
	int location = glGetAttribLocation(program, name.c_str());
	if (location < Shader::MIN_LOC) {
		GetLogger()->Error("Invalid Attribute: " + name);
		return MIN_LOC - 1;
	}
	attributes.insert(attributes.begin() + location, name);
	GetLogger()->Log("Registered Attribute: " + name);
	return location;
}

int ce::Shader::registerUniform(std::string name)
{
	int location = glGetUniformLocation(program, name.c_str());
	if (location < Shader::MIN_LOC) {
		GetLogger()->Error("Invalid Uniform: " + name);
		return MIN_LOC - 1;
	}
	uniforms.insert(uniforms.begin() + location, name);
	GetLogger()->Log("Registered Uniform: " + name);
	return location;
}


ce::Shader::Shader(const char* name ) :
	program(glCreateProgram())
{
	ShaderFile shaderFile = ce::AssetManager::getShaderFile("basic");

	int vertexShader = 0;
	int fragmentShader = 0;
	int geometryShader = 0;

	if (shaderFile.vertex != "") vertexShader = createShader(GetLogger(), GL_VERTEX_SHADER, shaderFile.vertex);
	if (shaderFile.fragment != "") fragmentShader = createShader(GetLogger(), GL_FRAGMENT_SHADER, shaderFile.fragment);
	if (shaderFile.geometry != "") geometryShader = createShader(GetLogger(), GL_GEOMETRY_SHADER, shaderFile.geometry);
	linkProgram(vertexShader, fragmentShader, vertexShader);
	
	int attrCount=0, uniformCount=0;
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attrCount);
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

	attributes.resize(attrCount);
	uniforms.resize(uniformCount);
}

ce::Shader::~Shader()
{
	glDeleteProgram(program);
}

void ce::Shader::bind()
{
	glUseProgram(program);
}

void ce::Shader::unbind()
{
	glUseProgram(0);
}

GLuint ce::Shader::getShader()
{
	return program;
}

GLuint ce::Shader::getAttribLocation(const std::string& name)
{
	if (attributes.size() < (size_t)Shader::MIN_LOC) return registerAttribute(name.c_str());
	auto location = std::find(attributes.begin(), attributes.end(), name);
	if (location != attributes.end())
		return std::distance(attributes.begin(), location);
	else
		return registerAttribute(name.c_str());
}

GLuint ce::Shader::getUniformLocation(const std::string& name)
{
	if (attributes.size() < (size_t)Shader::MIN_LOC) return registerUniform(name.c_str());
	auto location = std::find(uniforms.begin(), uniforms.end(), name);
	if (location != uniforms.end())
		return std::distance(uniforms.begin(), location);
	else
		return registerUniform(name.c_str());
}

void ce::Shader::vertexAttribPointer(std::string attrib, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	bind();
	GLuint location = getAttribLocation(attrib);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glVertexAttribPointer(location, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(location);
	unbind();
}

void ce::Shader::setBool(const std::string& name, bool value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform1i(location, (int)value);
	unbind();
}

void ce::Shader::setInt(const std::string& name, int value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform1i(location, value);
	unbind();
}

void ce::Shader::setFloat(const std::string& name, float value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform1f(location, value);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setVec2(const std::string& name, vec2& value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform2fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setVec2(const std::string& name, float x, float y)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform2f(location, x, y);
	//storageLog("uniform", name, &x, &y);
	unbind();
}
void ce::Shader::setVec3(const std::string& name, vec3& value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform3fv(location, 1, &value[0]);
	unbind();
}
void ce::Shader::setVec3(const std::string& name, float x, float y, float z)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform3f(location, x, y, z);
	//storageLog("uniform", name, &x, &y, &z);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setVec4(const std::string& name, vec4& value)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform4fv(location, 1, &value[0]);
	//storageLog("uniform", name, &value[0]);
	unbind();
}
void ce::Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniform4f(location, x, y, z, w);
	//storageLog("uniform", name, &x, &y, &z, &w);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat2(const std::string& name, mat2& mat)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
	//storageLog("uniform", name, &mat[0][0]);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat3(const std::string& name, mat3& mat)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
	//storageLog("uniform", name, &mat[0][0]);
	unbind();
}
// ------------------------------------------------------------------------
void ce::Shader::setMat4(const std::string& name, mat4& mat)
{
	bind();
	GLuint location = getUniformLocation(name);
	if (location < (GLuint)Shader::MIN_LOC) return;
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
	//storageLog("uniform", name, &mat[0][0]);
	unbind();
}

