/*!*************************************************************************
****
\file			Camera2D.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			02-11-2022
\brief			This file calculate the projection view matrix and aspect ratio
				and set our world coordinates to view coordinates

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
		: mProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mViewMatrix(1.0f),
		mPosition{ 0.0f, 0.0f, 0.0f }
	{ 
		mViewportWidth = mWindow.Getter().m_Width;
		mViewportHeight = mWindow.Getter().m_Height;
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	/*!*************************************************************************
	Set projection matrix
	****************************************************************************/
	void Camera2D::SetProjection(float left, float right, float bottom, float top)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	/*!*************************************************************************
	Use input mouse scroll wheel to adjust camera
	****************************************************************************/
	bool Camera2D::MouseScrolling()
	{
		
		if (p_Input->mMouseScrollStatus < 0 )
		{
			mZoomLevel -= 10.0f * Timer::GetInstance().GetGlobalDT();
		}
		else if (p_Input->mMouseScrollStatus > 0)
		{
			mZoomLevel += 10.0f * Timer::GetInstance().GetGlobalDT();;
		}
		mZoomLevel = std::max(mZoomLevel, 0.25f);
		mZoomLevel = std::min(mZoomLevel, 5.00f);
		p_Input->mMouseScrollStatus = 0.0f;

		SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
		RecalculateMatrix();
		return false;
	}

	/*!*************************************************************************
	Resize camera
	****************************************************************************/
	void Camera2D::Resize(float width, float height)
	{
		mAspectRatio = width / height;
		SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}

	/*!*************************************************************************
	Reset zoom level
	****************************************************************************/
	void Camera2D::resetZoomLevel()
	{
		mZoomLevel = 1.0f;
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
		mViewMatrix = glm::lookAt(mPosition, mPosition + front, up);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}
}