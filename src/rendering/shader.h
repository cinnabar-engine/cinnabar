#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <ce_assets.h>
#include <ce_math.h>

namespace ce {
	class Shader {
	 public:
		Shader(std::string name, std::map<std::string, std::string> options = {})
			: Shader(name, name, name, options){};
		Shader(std::string vertName, std::string fragName, std::map<std::string, std::string> options = {})
			: Shader(vertName, NULL, fragName, options){};
		Shader(std::string vertName, std::string geoName, std::string fragName, std::map<std::string, std::string> options = {});
		~Shader();

		void bind(), unbind();

		GLuint getShader();
		GLint
			getAttribLocation(const std::string name),
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
		inline static const GLint MIN_LOC = 0; // TODO: this has no value other than 0, why does it exist?

		GLuint m_program;
		std::vector<std::string> m_attributes, m_uniforms;

		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

		int registerAttribute(std::string name),
			registerUniform(std::string name);
	};
}
