#pragma once

#include <vector>

#include <cinnabar-core/transform.hpp>

#include <cinnabar-render/camera.hpp>
#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>
#include <cinnabar-render/window.hpp>

namespace ce {
	class RenderEngine {
	 public:
		typedef glm::uint32 BufferBit;
		extern static const BufferBit
			COLOR_BUFFER_BIT,
			DEPTH_BUFFER_BIT,
			STENCIL_BUFFER_BIT;

		typedef glm::uint32 DepthFunc;
		extern static const DepthFunc
			DEPTH_NEVER,
			DEPTH_LESS,
			DEPTH_EQUAL,
			DEPTH_LEQUAL,
			DEPTH_GREATER,
			DEPTH_NOTEQUAL,
			DEPTH_GEQUAL,
			DEPTH_ALWAYS;

		typedef glm::uint32 RenderOption;
		
			/*GL_BLEND,
			GL_CLIP_DISTANCE?,
			GL_CULL_FACE, // TODO: create cull settings function
			GL_DEBUG_OUTPUT,
			GL_DEBUG_OUTPUT_SYNCHRONOUS // TODO: glDebugMessageCallback
			GL_DEPTH_CLAMP // TODO: glDepthRange
			GL_DEPTH_TEST // TODO: glDepthRange
			GL_DITHER
			GL_FRAMEBUFFER_SRGB
			GL_LINE_SMOOTH // TODO: glLineWidth
			GL_MULTISAMPLE // TODO: glSampleCoverage
			GL_POLYGON_OFFSET_FILL // TODO: glPolygonOffset
			GL_POLYGON_OFFSET_LINE // TODO: glPolygonOffset
			GL_POLYGON_OFFSET_POINT // TODO: glPolygonOffset
			GL_POLYGON_SMOOTH
			GL_PRIMITIVE_RESTART // TODO: glPrimitiveRestartIndex
			GL_PRIMITIVE_RESTART_FIXED_INDEX
			GL_RASTERIZER_DISCARD // TODO: glClearBufferData glClearBufferSubData glClearTexImage glClearTexSubImage
			GL_SAMPLE_ALPHA_TO_COVERAGE
			GL_SAMPLE_ALPHA_TO_ONE // TODO: glSampleCoverage
			GL_SAMPLE_COVERAGE // TODO: glMinSampleShading
			GL_SAMPLE_SHADING // TODO: glMinSampleShading
			GL_SAMPLE_MASK // TODO: glSampleMaski
			GL_SCISSOR_TEST
			GL_STENCIL_TEST // TODO: glStencilFunc glStencilOp
			GL_PROGRAM_POINT_SIZE*/


		RenderEngine(glm::vec4 clearColor = glm::vec4());
		~RenderEngine();

		void setSize(glm::vec2 size);

		void setRenderOption(RenderOption option, bool enable); // TODO: create enum for option

		void setClearColor(glm::vec4 color);
		void setClearDepth(glm::float32 depth);
		void setClearStencil(glm::int32 stencil);

		void setDepthFunc(DepthFunc func);

		void clear(BufferBit buffer = DEPTH_BUFFER_BIT);
		void render(Mesh* mesh, Material* material, Transform* transform, Camera* camera);

	 private:
		void bind(Mesh* mesh, Material* material, Transform* transform, Camera* camera);
	};
}
