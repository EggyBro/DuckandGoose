/*!*************************************************************************
****
\file			Graphic.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			9-28-2022
\brief			This file contain neccessary function for graphic class

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "Platform/System/System.h"
#include "Platform/Graphics/Texture.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/matrix3D.h"
#include "ExoEngine/Math/physics.h"
#include "Camera2D.h"
#include "Platform/Window/Window.h"
#include "Renderer.h"
#include "Buffer.h"
#include "TextRendering.h"
#include "ExoEngine/Math/math.h"
#include "ExoEngine/Animation/Animation.h"

namespace EM {

	class Graphic : public System
	{
	public:
		
		//For Debugging Purposes
		virtual std::string GetName() { return "graphic"; }

		virtual void Init() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		
		inline static Camera2D camera { -1.0f, 1.0f, -1.0f , 1.0f };
		inline static Camera2D scene_camera { -1.0f, 1.0f, -1.0f , 1.0f };
		inline static Camera2D *mcamera = nullptr;
		bool misFps = false;
	private:
		//for testing
		std::unique_ptr<Renderer> mRenderer = std::make_unique<Renderer>();
		std::shared_ptr<Font> mFont = std::make_shared<Font>();
		MultiRefs<SpriteRender> mIndex1;
		WinData mWinData{};
		Animation mAimator;
	private:
		//void LoadTexture(std::string filename);
		void LoadIconsTexture(std::string filename);
	};
}