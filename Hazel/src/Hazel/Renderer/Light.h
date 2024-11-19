#pragma once

#include <glm/glm.hpp>

namespace Hazel {
	class Light {
	public:
		Light(glm::vec3 position) : m_Position(position) {}
		~Light() {}

		inline glm::vec3 GetPosition() const {
			return m_Position;
		}
		inline void SetPosition(glm::vec3 pos) {
			m_Position = pos;
		}
	private:
		glm::vec3 m_Position;
	};
}
