#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Camera.h"
#include "Shader.h"


namespace Hazel {

	class Renderer {
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix = glm::mat4(1.0f));

		static void Submit(const Ref<Shader>& shader, const Ref<VertexBuffer>& vertexBuffer, const glm::mat4& modelMatrix = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}