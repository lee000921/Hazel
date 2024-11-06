#include "hzpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Hazel {
	
	void Hazel::OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
	
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Hazel::OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Hazel::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray) {
		glDrawElements(GL_TRIANGLES, VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

