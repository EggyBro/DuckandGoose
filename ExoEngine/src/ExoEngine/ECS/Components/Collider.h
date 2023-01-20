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
			line, //---------LineSegment
			rect, //---------AABB
			box, //----------Playable area box
			button
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
		/*!*************************************************************************
		This function sets the collider type using the enum class as an input
		****************************************************************************/
		void SetCollider(ColliderType type) { mCol = type; }
		/*!*************************************************************************
		This function sets the collider type based on an int input
		****************************************************************************/
		void SetCollider(int type) 
		{
			if (static_cast<ColliderType>(type) < ColliderType::none || static_cast<ColliderType>(type) > ColliderType::button)
			{
				assert("Not a Valid Collider");
			}
			mCol = static_cast<ColliderType>(type);
		}
		/*!*************************************************************************
		This function sets the offset of the collider
		Offset is a vector which is added to position to get the origin point of the
		collider
		****************************************************************************/
		void SetOffset(vec2D input) { mOffset = input; }
		/*!*************************************************************************
		This function sets the minimum point for AABB colliders
		mMin is a vector which is added to the origin point of the collider to get
		the minimum point
		****************************************************************************/
		void SetMin(vec2D input) { mMin = input; }
		/*!*************************************************************************
		This function sets the maximum point for AABB colliders
		mMin is a vector which is added to the origin point of the collider to get
		the maximum point
		****************************************************************************/
		void SetMax(vec2D input) { mMax = input; }
		/*!*************************************************************************
		This function sets radius for circle colliders
		****************************************************************************/
		void SetRad(float input) { mRadius = input; }
		/*!*************************************************************************
		This function sets the hit boolean for the collider
		0 is no hit
		1 is hit
		****************************************************************************/
		void SetHit(int input) { mHit = input; }
		/*!*************************************************************************
		This function sets the normal for collision response in the event of a hit
		Collision response is calculated in the collision system and input here

		It will then be used by the collision response script to calculate the collision
		counter-force. 
		****************************************************************************/
		void SetNormal(vec2D input) { mCollisionNormal = input; }

		/*!*************************************************************************
		This function sets the active state of the collision component
		****************************************************************************/
		void ToggleAlive() { is_Alive = is_Alive ? false : true; }


		/*!*************************************************************************
		This function returns the collider type data member
		****************************************************************************/
		ColliderType& GetCollider() { return mCol; }
		/*!*************************************************************************
		This function returns the collider offset data member
		****************************************************************************/
		vec2D& GetOffset() { return mOffset; }
		/*!*************************************************************************
		This function returns the collider minimum point data member
		****************************************************************************/
		vec2D &GetMin() { return mMin; }
		/*!*************************************************************************
		This function returns the collider maximum point data member
		****************************************************************************/
		vec2D &GetMax() { return mMax; }
		/*!*************************************************************************
		This function returns the collider radius data member
		****************************************************************************/
		float &GetRad() { return mRadius; }
		/*!*************************************************************************
		This function returns the collider hit data member
		****************************************************************************/
		int GetHit() { return mHit; }
		/*!*************************************************************************
		This function returns the collider normal response data member
		****************************************************************************/
		vec2D GetNormal() { return mCollisionNormal; }
		/*!*************************************************************************
		This function returns the collider acctive state data member
		****************************************************************************/
		bool GetAlive() { return is_Alive; }

		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	private:
		ColliderType mCol{};
		vec2D mCollisionNormal;
		vec2D mMin;
		vec2D mMax;
		vec2D mOffset;
		int mHit;
		float mRadius;
		bool is_Alive;
	};
}