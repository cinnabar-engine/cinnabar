#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <cinnabar-render/types.hpp>
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

		glm::uint32 getShader();
		glm::int32
			getAttribLocation(const std::string name),
			getUniformLocation(const std::string name);

		void
			vertexAttribPointer(std::string attrib, glm::int32 size, GLenum type, bool normalized, glm::uint32 stride, const void* pointer), // TODO: deal with type
			vertexAttribPointer(Attribute attrib, glm::int32 size, GLenum type, bool normalized, glm::uint32 stride, const void* pointer);

		template <typename T>
		void setUniform(const std::string name, const T& value);
		template <typename T>
		void setUniform(glm::int32 location, const T& value);
		template <typename T>
		void setUniformArray(const std::string name, glm::uint32 count, const T* value);
		template <typename T>
		void setUniformArray(glm::int32 location, glm::uint32 count, const T* value);
		void
			setUniform(const std::string name, float x, float y),
			setUniform(const std::string name, float x, float y, float z),
			setUniform(const std::string name, float x, float y, float z, float w),

			setUniform(glm::int32 location, float x, float y),
			setUniform(glm::int32 location, float x, float y, float z),
			setUniform(glm::int32 location, float x, float y, float z, float w);

	 private:
		inline static const glm::int32 MIN_LOC = 0; // TODO: this has no value other than 0, why does it exist?

		glm::uint32 m_program;
		std::vector<std::string>
			m_attributes = {
				"aPosition",
				"aNormal",
				"aUV",
				"aColor",
			},
			m_uniforms;

		void linkProgram(glm::uint32 vertexShader, glm::uint32 fragmentShader, glm::uint32 geometryShader);

		//int registerAttribute(std::string name),
		//	registerUniform(std::string name);
	};
}
