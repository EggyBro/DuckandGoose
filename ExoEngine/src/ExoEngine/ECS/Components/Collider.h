/*!*****************************************************************************
\file Collider.cpp
\author Elton Teo Zhe Wei, Tan Ek Hern
\par DP email: e.teo@digipen.edu, t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 30-10-2022
\brief  This file contains the component declaration as well as member function
		definitions for the collider component of the game engine. 
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#pragma once
#include "IComponent.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM
{
	class Collider : public IComponent
	{
	public:
		/*!*************************************************************************
		This is the list of collider types. Collider type also informs response behavior
		****************************************************************************/
		enum class ColliderType
		{
			none,
			circle, //-------Circle
			bubble, //-------Non-physics Circle
			line, //---------LineSegment
			rect, //---------AABB
			box, //----------Playable area box
			button
		};

		struct Colpiece {
			ColliderType mCol;
			vec2D mCollisionNormal;
			vec2D mMin;
			vec2D mMax;
			vec2D mOffset;
			int mHit;
			float mRadius;
			bool is_Alive;
		};

		Collider();
		~Collider() = default;
		/*!*************************************************************************
		This function de-serializes the level colliders from the given level json file
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		This function saves the level information by serializing it to the level json 
		file
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
    
		Colpiece& operator[](int i) {
			return mColArr[i];
		}

		Colpiece* GetCollisionArray()
		{
			return mColArr;
		}

		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	private:
		Colpiece mColArr[2];
	};
}