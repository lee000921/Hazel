#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& VertexArray) override;

		virtual void Draw(const Ref<VertexBuffer>& vertexBuffer) override;

		virtual float GetTime() override;
	};

}