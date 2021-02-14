#ifndef _CE_RENDER_COMMAND_H_
#define _CE_RENDER_COMMAND_H_

#include "shader.h"
#include "texture.h"
#include "mesh.h"

namespace ce {
	struct RenderCommand {
		Shader* shader = NULL;
		Mesh* mesh = NULL;
		Texture* texture = NULL;
		unsigned point_count;
	};
}

#endif //_CE_RENDER_COMMAND_H_
