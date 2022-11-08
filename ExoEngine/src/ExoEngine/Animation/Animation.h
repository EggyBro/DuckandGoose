#pragma once
#include "Platform/Graphics/Renderer.h"
#include "Platform/Graphics/SpriteRendering.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM {

	class Animation
	{
	public:
		Animation();
		//void AddFrameInfo();
		void FrameIncrement();
		bool UpdateAnimation(float deltatime);
		void ResetFrame();
	private:
		//std::vector<FrameData> frames;
		float CurrentFrameTime; // this timer will decide how long to change to next frame
		//float CurrentFrameIndex;// currentFrameIndex
	};
}