/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-11-2022
\brief			Header file for animation.cpp

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
	    static std::unordered_map<std::string, std::vector<float>> spriteContainer;// to store all animation info
		Animation();
		void UpdateAnimation(float deltatime, Sprite& sprite);
		//std::unordered_map<std::string, std::vector<float>>& GetContainers() { return spriteContainer; }
	private:
	};
}