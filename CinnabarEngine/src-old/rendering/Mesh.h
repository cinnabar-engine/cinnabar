#ifndef _MESH_H_
#define _MESH_H_

#include <glad/glad.h>

#include "GLObject.h"
#include "Vertex.h"

namespace ce {
	class Mesh:public GLObject
	{

	private:
		unsigned vertexCount;
		unsigned indexCount;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		void initVAO(Vertex* vertexArray, GLuint* indexArray);
	public:
		Mesh(
			Vertex* vertexArray, const unsigned vertexCount,
			GLuint* indexArray = NULL, const unsigned indexCount = 0
		);
		~Mesh();
		void sendToShader(class Shader* shader);

		// Inherited via GLObject
		virtual Logger* GetLogger() override;
		unsigned GetIndexCount() { return indexCount; };
		virtual void destroy() override;
		virtual void bind() override;
		virtual void unbind() override;
	};
}

#endif // !_MESH_H_
