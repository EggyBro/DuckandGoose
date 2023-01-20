/*!*************************************************************************
****
\file			Camera2D.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			02-11-2022
\brief			This file header contain the declaration for camera function


Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

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

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(const glm::vec3& position) { mPosition = position; RecalculateMatrix(); }

		float GetRotation() const { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; RecalculateMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const{ return mViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; }
		
		float GetZoomLevel()const { return mZoomLevel; }
		void SetZoomLevel(float level) { mZoomLevel = level; }
		void resetZoomLevel();

		bool MouseScrolling();

		void Resize(float width, float height);
	private:

		glm::mat4 mProjectionMatrix ;
		glm::mat4 mViewMatrix;
		glm::mat4 mViewProjectionMatrix;
		glm::vec3 mPosition;
		
		float mRotation = 0.0f;
		unsigned int mViewportWidth, mViewportHeight;
		float mAspectRatio = 0.0f;
		float mZoomLevel = 1.0f;
		Window mWindow;

	private:
		void RecalculateMatrix();
	};
}
