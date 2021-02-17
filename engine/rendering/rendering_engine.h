#ifndef _RENDER_ENGINE_H_
#define _RENDER_ENGINE_H_


#include <vector>
#include <math/transform.h>
#include "material.h"
#include <ce_event_handler.h>
#include <core/window.h>

namespace ce {
	struct RenderCommand{
		Transform* transform;
		Material* material;
		Mesh* mesh;
		unsigned points;
	};
	
	class RenderingEngine {
	private:
		float 
		m_aspectRatio,
		m_fov;
		
		std::vector<RenderCommand> m_commands={};
		
		void clear();
		void bind(RenderCommand command);
		void render(unsigned count);
		void unbind(RenderCommand command);
	public:
		RenderingEngine();
		~RenderingEngine();
		
		void setFOV(float fov){m_fov = glm::radians(fov);};
		void setSize(glm::vec2 size);
		void setClearColor(glm::vec4 color);
		
		glm::mat4 getProjection();
		
		void registerCommand(RenderCommand command) {m_commands.push_back(command);}
		void render();
	};
}

#endif // _RENDER_ENGINE_H_
