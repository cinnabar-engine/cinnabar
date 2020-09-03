#ifndef _SHADER_H_
#define _SHADER_H_

#include <vector>
#include<glm/glm.hpp>
#include <glad/glad.h>
#include "GLObject.h"
#include "../ce_assets.h"
#include "../managers/AssetManager.h"

using namespace glm;

namespace ce {
	class Shader : public GLObject
	{
	private:
		inline static int MIN_LOC = 0;

		GLuint program;
		std::vector<std::string> attributes;
		std::vector<std::string> uniforms;

		void linkProgram(int vertexShader, int fragmentShader, int geometryShader);

		int registerAttribute(std::string name);
		int registerUniform(std::string name);
	public:
		Shader(ShaderFile shaderFile);
		~Shader();

		// Inherited via GLObject
		virtual Logger* GetLogger() override;
		virtual void destroy() override;
		virtual void bind() override;
		virtual void unbind() override;

		GLuint getShader();
		GLuint getAttribLocation(const std::string& name);
		GLuint getUniformLocation(const std::string& name);

		void vertexAttribPointer(std::string attrib, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);

		void setVec2(const std::string& name, vec2& value);
		void setVec2(const std::string& name, float x, float y);

		void setVec3(const std::string& name, vec3& value);
		void setVec3(const std::string& name, float x, float y, float z);

		void setVec4(const std::string& name, vec4& value);
		void setVec4(const std::string& name, float x, float y, float z, float w);

		void setMat2(const std::string& name, mat2& mat);
		void setMat3(const std::string& name, mat3& mat);
		void setMat4(const std::string& name, mat4& mat);
	};
}

#endif // !_SHADER_H_