#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <ce_math.h>

using namespace glm;

namespace ce {
	struct Vertex {
		vec3 position;
		vec4 color;
		vec2 texCoord;
	};
}

#endif // !_VERTEX_H_
