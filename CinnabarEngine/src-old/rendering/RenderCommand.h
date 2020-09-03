#ifndef _RENDER_COMMAND_H_
#define _RENDER_COMMAND_H_

#include "../ce_util.h"
#include "Material.h"

namespace ce {
	struct RenderCommand {
		Material* material = NULL;
		Mesh* mesh = NULL;
		unsigned pointCount = 0;
	};
}

#endif // !_RENDER_COMMAND_H_
