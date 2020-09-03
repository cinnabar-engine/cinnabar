#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>

#include "GLObject.h"
#include "../ce_assets.h"
#include "../managers/AssetManager.h"

namespace ce {

	class Texture: public GLObject
	{
	private:
		GLuint texture;
		int width, height, channelCount;
		unsigned int type;

	public:
		Texture(TextureFile file, GLenum type = GL_TEXTURE_2D);
		~Texture();


		// Inherited via GLObject
		virtual Logger* GetLogger() override;
		virtual void destroy() override;
		virtual void bind() override;
		void activate(int slot);
		virtual void unbind() override;
	};
}

#endif // !_TEXTURE_H_
