#include "empch.h"
#include "Camera2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "ExoEngine/Timer/Time.h"

namespace EM {
	Camera2D::Camera2D(float left, float right, float bottom, float top)//left, right, bottom and top
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f),
		m_Position{ 0.0f, 0.0f, 0.0f }, m_viewportWidth{0}, m_viewportHeight{0}
	{ 
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void Camera2D::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	bool Camera2D::MouseScrolling()
	{
		
		if (p_Input->MouseScrollStatus < 0 )
		{
			m_ZoomLevel -= 10.0f * Timer::GetInstance().GetGlobalDT();
		}
		else if (p_Input->MouseScrollStatus > 0)
		{
			m_ZoomLevel += 10.0f * Timer::GetInstance().GetGlobalDT();;
		}
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_ZoomLevel = std::min(m_ZoomLevel, 5.00f);
		p_Input->MouseScrollStatus = 0.0f;
		m_viewportWidth = m_window.Getter().m_Width;
		m_viewportHeight = m_window.Getter().m_Height;
		m_AspectRatio = (float)m_viewportWidth / (float)m_viewportHeight;

		SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	void Camera2D::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}