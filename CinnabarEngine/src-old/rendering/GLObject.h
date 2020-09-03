#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

#include "../core/CEObject.h"

namespace ce {
	class GLObject : public Object {
	private:
	public:
		GLObject() {};

		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}

#endif // !_GL_OBJECT_H_