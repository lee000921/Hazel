#include "hzpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		// m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::BeginScene(Camera& camera) {
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_View", m_SceneData->ViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Projection", m_SceneData->ProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", modelMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexBuffer>& vertexBuffer, const glm::mat4& modelMatrix) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_View", m_SceneData->ViewMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Projection", m_SceneData->ProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", modelMatrix);

		vertexBuffer->Bind();

		RenderCommand::Draw(vertexBuffer);
	}

}