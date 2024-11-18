#include "hzpch.h"
#include "Camera.h"

#include "Hazel/Input.h"


#include <Hazel/KeyCodes.h>
#include <Hazel/MouseButtonCodes.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#define M_PI 3.14159f

namespace Hazel {

	void Camera::UpdateRotation(float xOffset, float yOffset) {
	
		m_Yaw += xOffset;
		m_Pitch -= yOffset;

		if (m_Pitch > 89.0f) {
			m_Pitch = 89.0f;
		}
		if (m_Pitch < -89.0f) {
			m_Pitch = -89.0f;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
		front.y = sin(glm::radians(m_Pitch));
		front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));

		m_Direction = glm::normalize(front);
	}

	void Camera::UpdateFov(float xOffset, float yOffset) {
		
		if (m_FOV >= 1.0f && m_FOV <= 45.0f) {
			m_FOV -= yOffset;
		}
		if (m_FOV <= 1.0f) {
			m_FOV = 1.0f;
		}
		if (m_FOV >= 45.0f) {
			m_FOV = 45.0f;
		}
	}
	
}