#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace Hazel {

	void OpenGLRendererAPI::Init() {
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray) {
		// glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
	}

	void OpenGLRendererAPI::Draw(const Ref<VertexBuffer>& vertexBuffer) {
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	float OpenGLRendererAPI::GetTime() {

		return (float)glfwGetTime();

	}
}

