/*!*************************************************************************
****
\file			Camera2D.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			02-11-2022
\brief			This file calculate the projection view matrix and aspect ratio
				and set our world coordinates to view coordinates
****************************************************************************
***/
#include "empch.h"
#include "Camera2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "ExoEngine/Timer/Time.h"

namespace EM {

	/*!*************************************************************************
	Constructor for Camera2D
	****************************************************************************/
	Camera2D::Camera2D(float left, float right, float bottom, float top)//left, right, bottom and top
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f),
		m_Position{ 0.0f, 0.0f, 0.0f }
	{ 
		m_viewportWidth = m_window.Getter().m_Width;
		m_viewportHeight = m_window.Getter().m_Height;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	/*!*************************************************************************
	Set projection matrix
	****************************************************************************/
	void Camera2D::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	/*!*************************************************************************
	Use input mouse scroll wheel to adjust camera
	****************************************************************************/
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

		SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		RecalculateMatrix();
		return false;
	}

	/*!*************************************************************************
	Resize camera
	****************************************************************************/
	void Camera2D::Resize(float width, float height)
	{
		m_AspectRatio = width / height;
		SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	/*!*************************************************************************
	Reset zoom level
	****************************************************************************/
	void Camera2D::resetZoomLevel()
	{
		m_ZoomLevel = 1.0f;
	}

	/*!*************************************************************************
	Recalculate Camera2D matrix
	****************************************************************************/
	void Camera2D::RecalculateMatrix()
	{
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(front, worldup));
		glm::vec3 up = glm::normalize(glm::cross(right, front));
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + front, up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}