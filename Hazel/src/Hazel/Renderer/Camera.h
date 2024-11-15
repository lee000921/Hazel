#pragma once

#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {
	class Camera {

	public:
		Camera(glm::vec3& position, glm::vec3& direction, glm::vec3& up, float fov, float ratio) :
			m_Position(position),
			m_Direction(direction),
			m_Up(up),
			m_FOV(fov),
			m_Ratio(ratio) {}
		~Camera() {};

		inline glm::mat4 GetViewMatrix() const {
			/*glm::mat4 view;
			view = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
			return view;*/

			float radius = 10.0f;
			float time = RenderCommand::GetTime();
			float camX = sin(time) * radius;
			float camZ = cos(time) * radius;

			glm::mat3 view;
			view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			return view;
		}

		inline glm::mat4 GetProjectionMatrix() const {

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(m_FOV), m_Ratio, 0.1f, 100.0f);
			return projection;
		}

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Up;
		float m_FOV;
		float m_Ratio;
	};
}