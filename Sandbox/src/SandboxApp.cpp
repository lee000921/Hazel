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


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;		
			layout(location = 1) in vec3 a_Normal;
			layout(location = 2) in vec2 a_TexCoord;

			out vec3 v_Normal;
			out vec3 v_Pos;
			out vec2 v_TexCoord;
			
			uniform mat4 u_Projection;
			uniform mat4 u_View;
			uniform mat4 u_Model;

			void main() 
			{	
				gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
				v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
				v_Pos = vec3(u_Model * vec4(a_Position, 1.0));
				v_TexCoord = a_TexCoord;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			struct Material {
				sampler2D diffuse;
				sampler2D specular;
				float shininess;
			};

			struct Light {
				vec3 position;
				// vec3 direction;				

				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				
				float constant;
				float linear;
				float quadratic;
			};

			uniform Light light;
			uniform Material material;
			
			layout(location = 0) out vec4 color;	

			in vec3 v_Normal;
			in vec3 v_Pos;
			in vec2 v_TexCoord;
			
			uniform vec3 objectColor;
			uniform vec3 lightColor;	
			uniform vec3 viewPos;

			void main()
			{	
				float distance = length(light.position - v_Pos);
				float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
				// 环境光
				vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoord));

				// 漫反射
				vec3 norm = normalize(v_Normal);
				// vec3 lightDir = normalize(-light.direction);
				vec3 lightDir = normalize(light.position - v_Pos);
				float diff = max(dot(norm, lightDir), 0.0f);
				vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoord));

				// 镜面光
				vec3 viewDir = normalize(viewPos - v_Pos);
				vec3 reflectDir = reflect(-lightDir, norm);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
				vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoord));

				vec3 result = (ambient + diffuse + specular) * attenuation;
				color = vec4(result, 1.0f);
			}
		)";

		std::string lightFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;	
			
			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_CubeShader = Hazel::Shader::Create(vertexSrc, fragmentSrc);
		m_LightShader = Hazel::Shader::Create(vertexSrc, lightFragmentSrc);

		/*m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture->Bind();*/

		m_CubeTexture = Hazel::Texture2D::Create("assets/textures/container2.png");
		m_CubeTexture->Bind();

		m_CubeSpecularTexture = Hazel::Texture2D::Create("assets/textures/container2_specular.png");
		m_CubeSpecularTexture->Bind(1);

		

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

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("light.position", lightPos);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("light.ambient", ambientColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("light.diffuse", diffuseColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat3("light.specular", lightColor);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("light.constant", 1.0f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("light.linear", 0.09f);
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_CubeShader)->UploadUniformFloat("light.quadratic", 0.032f);


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

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Hazel::RenderCommand::Clear(); 
		
		Hazel::Renderer::Submit(m_LightShader, m_LightVertexArray, model);


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