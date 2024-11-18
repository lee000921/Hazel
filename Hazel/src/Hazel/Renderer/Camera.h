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
			glm::mat4 view;
			view = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
			
			return view;
		}

		inline glm::mat4 GetProjectionMatrix() const {

			glm::mat4 projection;
			projection = glm::perspective(glm::radians(m_FOV), m_Ratio, 0.1f, 100.0f);
			return projection;
		}

		inline glm::vec3& GetPosition() {
			return m_Position;
		}

		inline glm::vec3& GetDirection() {
			return m_Direction;
		}

		inline glm::vec3& GetUp() {
			return m_Up;
		}

		inline float& GetYaw() {
			return m_Yaw;
		}

		inline float& GetPitch() {
			return m_Pitch;
		}

		inline float& GetFov() {
			return m_FOV;
		}

		void UpdateRotation(float xOffset, float yOffset);

		void UpdateFov(float xOffset, float yOffset);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Up;
		float m_FOV;
		float m_Ratio;
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
	};
}