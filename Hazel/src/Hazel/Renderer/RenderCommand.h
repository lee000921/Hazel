#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand {
	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void Draw(const Ref<VertexBuffer>& vertexBuffer) {
			s_RendererAPI->Draw(vertexBuffer);
		}

		inline static float GetTime() {
			return s_RendererAPI->GetTime();
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}