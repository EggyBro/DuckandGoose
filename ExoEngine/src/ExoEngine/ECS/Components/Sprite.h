/*!*************************************************************************
****
\file			Sprite.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-2-2022
\brief			This file contain the declaration function for Sprite class
				which is the component for sprite rendering

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"
//#include "Platform/Graphics/Texture.h"

namespace EM {

	class Sprite : public IComponent
	{
	public:
		struct Coordinates
		{
			int x; int y;
			
		}Index;
		
		Sprite();
		~Sprite() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		void SetTexture(const std::string& name) { mTextureName = name; }
		std::string &GetTexture() { return mTextureName; }

		void SetIndex(int& x, int& y) { Index.x = x, Index.y = y; } // y will always remind as zero
		Coordinates& GetIndex() { return Index; }

		std::vector<float>&GetDisplayTime() { return displayTime; }
		int& GetMaxIndex() { return MaxIndex_X; }
		void SetUVCoor(float& u, float& v) { mUVcooridnates.x = u; mUVcooridnates.y = v; } 
		vec2D& GetUVCoor() { return mUVcooridnates; }

		void SetAlpha(float in) { mAlpha = in; }
		float GetAlpha() { return mAlpha; }

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	public:
	
		bool is_SpriteSheet; // to tell whether we are using a spritesheet
		bool is_Animated;	// if is a spritesheet do we want it to be animated 
		float internaltimer;
		//altas 
	private:
		std::string mTextureName;
		vec2D mUVcooridnates;
		float mAlpha;
		int MaxIndex_X;
		std::vector<float>displayTime;
		//TODO insert a increment for mIndex so that it can lease with the mAimator
	};
}