#pragma once
#include "glm/glm.hpp" //for ortho, perspective and other matrices
#include "Platform/Window/Window.h"
#include "ExoEngine/Timer/Time.h"
namespace EM {

	class Camera2D
	{
	public:
		Camera2D(float left, float right, float bottom, float top);//left, right, bottom and top

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		
		float GetZoomLevel()const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		bool MouseScrolling();
	private:

		glm::mat4 m_ProjectionMatrix ;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;
		
		float m_Rotation = 0.0f;
		unsigned int m_viewportWidth, m_viewportHeight;
		float m_AspectRatio = 0.0f;
		float m_ZoomLevel = 1.0f;
		Window m_window;

	private:
		void RecalculateMatrix();
	};
}
