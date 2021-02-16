#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <ce_rendering.h>
#include <ce_assets.h>
#include <managers/asset_manager.h>

namespace ce {

	class Texture
	{
	private:
		GLuint texture;
		int width, height, channelCount;
		unsigned int type;

	public:
		Texture(std::string filename, GLenum type = GL_TEXTURE_2D);
		~Texture();


		// Inherited via GLObject
		Logger* GetLogger();
		void bind();
		void unbind();
		void activate(int slot);
	};
}

#endif // !_TEXTURE_H_
