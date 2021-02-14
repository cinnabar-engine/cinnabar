#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "ce_gl.h"
#include <ce_assets.h>
#include <managers/asset_manager.h>

namespace ce {

	class Texture: public GLObject
	{
	private:
		GLuint texture;
		int width, height, channelCount;
		unsigned int type;

	public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		~Texture();


		// Inherited via GLObject
		virtual Logger* GetLogger();
		virtual void bind() override;
		void activate(int slot);
		virtual void unbind() override;
	};
}

#endif // !_TEXTURE_H_
