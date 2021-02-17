#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <ce_assets.h>
#include <ce_math.h>
#include <ce_rendering.h>

using namespace glm;

namespace ce {
	class Shader {
	 private:
		inline static int MIN_LOC = 0;

		GLuint program;
		std::vector<std::string> attributes, uniforms;

		void linkProgram(
			int vertexShader, int fragmentShader, int geometryShader);

		int registerAttribute(std::string name),
			registerUniform(std::string name);

	 public:
		Shader(const char* name);
		~Shader();

		void bind(), unbind();

		GLuint getShader(), getAttribLocation(const std::string name),
			getUniformLocation(const std::string name);

		void vertexAttribPointer(std::string attrib, GLint size, GLenum type,
			GLboolean normalized, GLsizei stride, const void*pointer),

			setBool(const std::string name, bool value),
			setInt(const std::string name, int value),
			setFloat(const std::string name, float value),

			setVec2(const std::string name, vec2 value),
			setVec2(const std::string name, float x, float y),

			setVec3(const std::string name, vec3 value),
			setVec3(const std::string name, float x, float y, float z),

			setVec4(const std::string name, vec4 value),
			setVec4(const std::string name, float x, float y, float z, float w),

			setMat2(const std::string name, mat2 mat),
			setMat3(const std::string name, mat3 mat),
			setMat4(const std::string name, mat4 mat);
	};
}