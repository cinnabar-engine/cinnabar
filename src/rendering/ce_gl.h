#ifndef _CE_GL_H_
#define _CE_GL_H_

#include <GL/glew.h>
#include <GL/wglew.h>
#include <SDL.h>
#ifdef __IPHONEOS__
#include <SDL_opengles.h> // we want to use OpenGL ES
#else
#include <SDL_opengl.h> // otherwise we want to use OpenGL
#endif

#include "../managers/asset_manager.h"

namespace ce {
	class GLObject {
	public:
		virtual void bind()=0;
		virtual void unbind()=0;
	};
}

#endif // !_CE_GL_H_
