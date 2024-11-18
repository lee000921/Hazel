#include <Hazel.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer(int width, int height) : 
		Layer("Example"),
		m_Camera(glm::vec3(0.0f, 0.0f, 3.0f), 
			     glm::vec3(0.0f, 0.0f, -1.0f), 
				 glm::vec3(0.0f, 1.0f, 0.0f),
				 45.0f, (float)width/height) {	

		m_VertexArray = Hazel::VertexArray::Create();

		/*float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};*/

		float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		// m_VertexArray
		m_VertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float2, "a_Texcoord"}
		});

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		Hazel::Ref<Hazel::IndexBuffer> IB = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(IB);*/


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;		
			
			uniform mat4 u_Projection;
			uniform mat4 u_View;
			uniform mat4 u_Model;

			void main() 
			{	
				gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;		

			void main()
			{
				color = vec4(0.8f, 0.2f, 0.3f, 1.0f);
			}
		)";

		/*m_Shader = Hazel::Shader::Create(vertexSrc, fragmentSrc);*/

		m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture->Bind();

		

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	

			uniform mat4 u_View;
			uniform mat4 u_Projection;
			uniform mat4 u_Transform;		


			void main()
			{	
				gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;	
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_View;
			uniform mat4 u_Projection;
			uniform mat4 u_Model;		

			out vec2 v_TexCoord;

			void main()
			{	
				v_TexCoord = a_TexCoord;
				gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;			

			uniform sampler2D u_Texture;			

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader = Hazel::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc);
		lastX = width / 2;
		lastY = height / 2;
}

	void OnUpdate(Hazel::Timestep ts) override {

		auto& cameraPos = m_Camera.GetPosition();
		auto& cameraDirection = m_Camera.GetDirection();
		auto& cameraUp = m_Camera.GetUp();

		if (Hazel::Input::IsKeyPressed(HZ_KEY_W)) {
			cameraPos += m_CameraMoveSpeed * ts * cameraDirection;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S)) {
			cameraPos -= m_CameraMoveSpeed * ts * cameraDirection;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
			cameraPos -= m_CameraMoveSpeed * ts * glm::normalize(glm::cross(cameraDirection, cameraUp));
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D)) {
			cameraPos += m_CameraMoveSpeed * ts * glm::normalize(glm::cross(cameraDirection, cameraUp));
		}

		 // if (Hazel::Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_LEFT)) {
		auto [xPos, yPos] = Hazel::Input::GetMousePosition();
		if (firstMouse) {
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}
		float xOffset = xPos - lastX;
		float yOffset = yPos - lastY;
		xOffset *= m_CameraRotationSpeed;
		yOffset *= m_CameraRotationSpeed;
		lastX = xPos;
		lastY = yPos;

		m_Camera.UpdateRotation(xOffset, yOffset);
		
		 // }

		Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Hazel::RenderCommand::Clear(); 

		// m_VertexBuffer->Bind();
		
		m_VertexArray->Bind();
		m_Shader->Bind();

		float time = Hazel::RenderCommand::GetTime();

		float radius = 10.0f;
		float camX = sin(time) * radius;
		float camZ = cos(time) * radius;

		glm::mat4 view = m_Camera.GetViewMatrix();
		
		glm::mat4 projection = m_Camera.GetProjectionMatrix();
		
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformMat4("u_Projection", projection);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformMat4("u_View", view);
		// std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformMat4("u_Model", model);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (i % 3 == 0) {
				angle = Hazel::RenderCommand::GetTime() * 55.0f;
			}
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->UploadUniformMat4("u_Model", model);

			Hazel::Renderer::Submit(m_Shader, m_VertexBuffer);
		}

		
		// Hazel::Renderer::Submit(m_Shader, m_VertexArray);
		/*m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);*/

		/*glm::mat4 view = m_Camera.GetViewMatrix();

		glm::mat4 projection = m_Camera.GetProjectionMatrix();

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));*/

		// Thought: Why not create a material object and let shader choose which material it load?
		// 从某个方面来说 material应该是对于要渲染的物体来说的 
		// 所以这里的方式是渲染物体时需要几何信息 + 材质，材质会绑定Shader
		// Hazel::Material* material = new Hazel::Material(m_FlatColorShader); 

		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformMat4("u_Projection", projection);
		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformMat4("u_View", view);

		//for (int y = 0; y < 20; y++) {
		//	for (int x = 0; x < 20; x++) {
		//		glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
		//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		//		Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		//	}
		//}

		//m_Texture->Bind();
		//Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//m_ChernoLogoTexture->Bind();
		//Hazel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//// Triangle
		//// Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		//Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override {
		Hazel::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Hazel::MouseScrolledEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnMouseScrolledEvent));
	}

	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event) {
		return false;
	}

	bool OnMouseScrolledEvent(Hazel::MouseScrolledEvent& event) {

		double xOffset = event.GetXOffset();
		double yOffset = event.GetYOffset();
		m_Camera.UpdateFov(xOffset, yOffset);
		return false;
	}
private:
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;
	
	// Hazel::OrthographicCamera m_Camera;
	Hazel::Camera m_Camera;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 0.05f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	bool firstMouse = true;
	float lastX, lastY;
};

class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		auto& window = GetWindow();
		int width = window.GetWidth();
		int height = window.GetHeight();
		PushLayer(new ExampleLayer(width, height));
	}

	~Sandbox() {

	}
};

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox();
}