#ifndef _CE_GL_H_
#define _CE_GL_H_

#include <GL/glew.h>

#include <SDL.h>

#include <managers/asset_manager.h>

namespace ce {
	class GLObject {
	public:
		virtual void bind()=0;
		virtual void unbind()=0;
	};
}

#endif // !_CE_GL_H_
