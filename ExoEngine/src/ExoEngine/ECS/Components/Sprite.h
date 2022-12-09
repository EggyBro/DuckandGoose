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
****************************************************************************
***/
#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"
#include "Platform/Graphics/Texture.h"
namespace EM {

	class Sprite : public IComponent
	{
	public:
		Sprite();
		~Sprite() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		void SetTexture(const std::string& name) { m_texturename = name; }
		std::string &GetTexture() { return m_texturename; }

		void SetIndex(float& x) { m_index.x = x; } // y will always remind as zero
		vec2D& GetIndex() { return m_index; }

		void SetDisplayTime(float displaytime) { mDisplayTime = displaytime; };
		float& GetDisplayTime() { return mDisplayTime; }


		void SetUVCoor(float& u, float& v) { mUVcooridnates.x = u; mUVcooridnates.y = v; } 
		vec2D& GetUVCoor() { return mUVcooridnates; }


		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	public:
		bool mIsSpriteSheet; // to tell whether we are using a spritesheet
		bool mIsanimated;	// if is a spritesheet do we want it to be animated 
		//altas 
	private:
		std::string m_texturename;
		vec2D m_index, mUVcooridnates;
		float mDisplayTime;
		//TODO insert a increment for mIndex so that it can lease with the animator
	};
}