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
		enum struct Attribute {
			POSITION,
			NORMAL,
			UV,
			COLOR,
		};
		enum struct Uniform {
			
		};

		Shader(std::string name, std::map<std::string, std::string> options = {})
			: Shader(name, name, name, options){};
		Shader(std::string vertName, std::string fragName, std::map<std::string, std::string> options = {})
			: Shader(vertName, "", fragName, options){};
		Shader(std::string vertName, std::string geoName, std::string fragName, std::map<std::string, std::string> options = {});
		~Shader();

		void bind(), unbind();

		GLuint getShader();
		GLint
			getAttribLocation(const std::string name),
			getUniformLocation(const std::string name);

		void
			vertexAttribPointer(std::string attrib, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer),
			vertexAttribPointer(Attribute attrib, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

		template <typename T>
		void setUniform(const std::string name, T value);
		void
			setUniform(const std::string name, float x, float y),
			setUniform(const std::string name, float x, float y, float z),
			setUniform(const std::string name, float x, float y, float z, float w),

			setUniform(GLint location, bool value),
			setUniform(GLint location, int value),
			setUniform(GLint location, float value),
			setUniform(GLint location, glm::vec2 value),
			setUniform(GLint location, glm::vec3 value),
			setUniform(GLint location, glm::vec4 value),
			setUniform(GLint location, glm::mat2 mat),
			setUniform(GLint location, glm::mat3 mat),
			setUniform(GLint location, glm::mat4 mat),

			setUniform(GLint location, float x, float y),
			setUniform(GLint location, float x, float y, float z),
			setUniform(GLint location, float x, float y, float z, float w);

	 private:
		inline static const GLint MIN_LOC = 0; // TODO: this has no value other than 0, why does it exist?

		GLuint m_program;
		std::vector<std::string>
			m_attributes = {
				"aPosition",
				"aNormal",
				"aUV",
				"aColor",
			},
			m_uniforms = {
				
			};

		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

		int registerAttribute(std::string name),
			registerUniform(std::string name);
	};
}
