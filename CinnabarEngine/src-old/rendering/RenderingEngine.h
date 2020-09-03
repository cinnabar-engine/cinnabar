#ifndef _RENDERING_ENGINE_H_
#define _RENDERING_ENGINE_H_

#include <vector>
#include "ce_render_libs.h"

namespace ce {
	class RenderingEngine {
	private:
		void clear(glm::vec4 color = glm::vec4(0, 0, 0, 0));
		void render(unsigned count);
		void bind(RenderCommand command);
		void unbind(RenderCommand command);

		std::vector<RenderCommand> commands;
	public:
		RenderingEngine();
		~RenderingEngine();
		void LoadCommand(RenderCommand command) { commands.push_back(command); };

		void render();


	};
}

#endif // !_RENDERING_ENGINE_H_
