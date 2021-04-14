#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <ce_assets.h>
#include <ce_math.h>
#include <GL/glew.h>

namespace ce {
	class Shader {
	 public:
		Shader(const char* name, std::map<std::string, std::string> options = {})
			: Shader(name, name, name, options) {};
		Shader(const char* vertName, const char* fragName, std::map<std::string, std::string> options = {})
			: Shader(vertName, NULL, fragName, options) {};
		Shader(const char* vertName, const char* geoName, const char* fragName, std::map<std::string, std::string> options = {});
		~Shader();

		void bind(), unbind();

		GLuint getShader(), getAttribLocation(const std::string name),
			getUniformLocation(const std::string name);

		void vertexAttribPointer(std::string attrib, GLint size, GLenum type,
			GLboolean normalized, GLsizei stride, const void* pointer);

		void
			setBool(const std::string name, bool value),
			setInt(const std::string name, int value),
			setFloat(const std::string name, float value),

			setVec2(const std::string name, glm::vec2 value),
			setVec2(const std::string name, float x, float y),

			setVec3(const std::string name, glm::vec3 value),
			setVec3(const std::string name, float x, float y, float z),

			setVec4(const std::string name, glm::vec4 value),
			setVec4(const std::string name, float x, float y, float z, float w),

			setMat2(const std::string name, glm::mat2 mat),
			setMat3(const std::string name, glm::mat3 mat),
			setMat4(const std::string name, glm::mat4 mat);
	 private:
		inline static int MIN_LOC = 0;

		GLuint m_program;
		std::vector<std::string> m_attributes, m_uniforms;

		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

		int registerAttribute(std::string name),
			registerUniform(std::string name);
	};
}
