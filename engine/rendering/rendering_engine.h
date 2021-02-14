#ifndef _CE_RENDERING_ENGINE_H_
#define _CE_RENDERING_ENGINE_H_

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "render_command.h"

namespace ce {
	class RenderingEngine {
	private:
		std::vector<RenderCommand> commands;
		
		void clear(glm::vec4 color = glm::vec4(0,0,0,0));
		void render(unsigned count);
		void bind(RenderCommand command);
		void unbind(RenderCommand command);
	public:
		RenderingEngine();
		~RenderingEngine();
		
		void render();
		void loadCommand(RenderCommand command) {commands.push_back(command);}
	};
}

#endif //_CE_RENDERING_ENGINE_H_
