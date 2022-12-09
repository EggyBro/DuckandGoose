/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-11-2022
\brief			Header file for animation.cpp
****************************************************************************
***/
#pragma once
#include "Platform/Graphics/Renderer.h"
#include "Platform/Graphics/SpriteRendering.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM {

	class Animation
	{
	public:
		struct FrameData
		{
			unsigned int TextureId; // which spritesheet is it using
			float DisplayTime;		// how long does the frame last before changing the next frame
			vec2D FrameIndex;		// the increment of the frame set to 0 when reach the last frame and y will always remind 0
			float MaxFrame;			// To check for the last frame
		};
		Animation();
		void AddFrameInfo(Sprite& sprite);
		const FrameData* GetCurrentFrame() const;
		bool UpdateAnimation(float deltatime);
		void ResetFrame();

	private:
		void FrameIncrement();

	private:
		
		std::vector<FrameData> frames;
		float CurrentFrameIndex;// currentFrameIndex
		float currentFrameTime; // decide when to transition to the next frame
		
	};
}