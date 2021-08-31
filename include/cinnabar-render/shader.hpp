#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cinnabar-render/assets.hpp>

namespace ce {
	class Shader {
	 public:
		enum struct Attribute {
			POSITION,
			NORMAL,
			UV,
			COLOR,
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
		void setUniform(const std::string name, const T& value);
		template <typename T>
		void setUniform(GLint location, const T& value);
		template <typename T>
		void setUniformArray(const std::string name, GLsizei count, const T* value);
		template <typename T>
		void setUniformArray(GLint location, GLsizei count, const T* value);
		void
			setUniform(const std::string name, float x, float y),
			setUniform(const std::string name, float x, float y, float z),
			setUniform(const std::string name, float x, float y, float z, float w),

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
			m_uniforms;

		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);

		//int registerAttribute(std::string name),
		//	registerUniform(std::string name);
	};
}
