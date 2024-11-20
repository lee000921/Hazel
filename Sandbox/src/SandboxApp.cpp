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
		
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};
		m_CubeVertexArray = Hazel::VertexArray::Create();

		
		// m_VertexArray
		Hazel::Ref<Hazel::VertexBuffer> cubeVB = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		cubeVB->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float3, "a_Normal"},
			{ Hazel::ShaderDataType::Float2, "a_TexCoord"}
		});

		m_CubeVertexArray->AddVertexBuffer(cubeVB);


		/*unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		Hazel::Ref<Hazel::IndexBuffer> IB = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(IB);*/

		m_LightVertexArray = Hazel::VertexArray::Create();
		Hazel::Ref<Hazel::VertexBuffer> lightVB = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		lightVB->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position"},
			{ Hazel::ShaderDataType::Float3, "a_Normal"},
			{ Hazel::ShaderDataType::Float2, "a_TexCoord"}
		});

		m_LightVertexArray->AddVertexBuffer(lightVB);

		m_CubeShader = Hazel::Shader::Create("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");
		m_LightShader = Hazel::Shader::Create("assets/shaders/vertex.vs", "assets/shaders/lightFragment.fs");

		/*m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture->Bind();*/

		m_CubeTexture = Hazel::Texture2D::Create("assets/textures/container2.png");
		m_CubeTexture->Bind();

		m_CubeSpecularTexture = Hazel::Texture2D::Create("assets/textures/container2_specular.png");
		m_CubeSpecularTexture->Bind(1);

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
		

		float time = Hazel::RenderCommand::GetTime();
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glm::vec3 lightColor(1.0f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		m_CubeShader->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("viewPos", m_Camera.GetPosition());
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformInt("material.diffuse", 0);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformInt("material.specular", 1);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("material.shininess", 32.0f);

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("dirLight.ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("dirLight.diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("dirLight.specular", lightColor);

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[0].position", pointLightPositions[0]);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[0].ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[0].diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[0].specular", lightColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[0].constant", 1.0f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[0].linear", 0.09f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[0].quadratic", 0.032f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[1].position", pointLightPositions[1]);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[1].ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[1].diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[1].specular", lightColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[1].constant", 1.0f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[1].linear", 0.09f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[1].quadratic", 0.032f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[2].position", pointLightPositions[2]);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[2].ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[2].diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[2].specular", lightColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[2].constant", 1.0f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[2].linear", 0.09f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[2].quadratic", 0.032f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[3].position", pointLightPositions[3]);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[3].ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[3].diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("pointLights[3].specular", lightColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[3].constant", 1.0f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[3].linear", 0.09f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("pointLights[3].quadratic", 0.032f);

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("spotLight.direction", m_Camera.GetDirection());
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("spotLight.position", m_Camera.GetPosition());
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("spotLight.ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("spotLight.diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("spotLight.specular", lightColor);

		m_LightShader->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_LightShader)->UploadUniformFloat3("u_Color", lightColor);

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

		

		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Hazel::RenderCommand::Clear(); 

		for (int i = 0; i < 4; i++) {

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			Hazel::Renderer::Submit(m_LightShader, m_LightVertexArray, model);
		}
		


		for (int i = 0; i < 10; i++) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			Hazel::Renderer::Submit(m_CubeShader, m_CubeVertexArray, model);
		}
		
		

		Hazel::Renderer::EndScene();
		
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
	Hazel::Ref<Hazel::Shader> m_CubeShader, m_LightShader;
	Hazel::Ref<Hazel::VertexArray> m_CubeVertexArray;
	Hazel::Ref<Hazel::VertexArray> m_LightVertexArray;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;
	Hazel::Ref<Hazel::Texture2D> m_CubeTexture;
	Hazel::Ref<Hazel::Texture2D> m_CubeSpecularTexture;
	
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