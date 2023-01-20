/*!*****************************************************************************
\file Collider.h
\author Elton Teo Zhe Wei, Tan Ek Hern
\par DP email: e.teo@digipen.edu, t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 30-10-2022
\brief  This file contains function definitions for some of the collider
		component's member functions
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "Collider.h"

namespace EM
{
	/*!*************************************************************************
	This is the constructor for the collider component to initialize all data members
	Data members will be changed during the de-serialization function call if the
	specific entity has serialized collider information
	****************************************************************************/
	Collider::Collider() : mCol{ ColliderType::none }, mMin{ vec2D(1.0f,1.0f) }, mMax{ vec2D(1.0f,1.0f) }, mRadius{ 0.3f }, mHit{ 0 }, mCollisionNormal{ vec2D() }, is_Alive{true} {}
	/*!*************************************************************************
	This function de-serializes the level colliders from the given level json file
	****************************************************************************/
	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		mCol = static_cast<ColliderType>(obj["ColliderType"].GetInt());
		mMin = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		mMax = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		mOffset = vec2D(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat());
		mRadius = obj["radius"].GetFloat();
		return true;
	}
	/*!*************************************************************************
	This function saves the level information by serializing it to the level json 
	file
	****************************************************************************/
	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ColliderType");
		writer->Int(static_cast<int>(mCol));
		writer->Key("minX");
		writer->Double(mMin.x);
		writer->Key("minY");
		writer->Double(mMin.y);
		writer->Key("maxX");
		writer->Double(mMax.x);
		writer->Key("maxY");
		writer->Double(mMax.y);
		writer->Key("offsetX");
		writer->Double(mOffset.x);
		writer->Key("offsetY");
		writer->Double(mOffset.y);
		writer->Key("radius");
		writer->Double(mRadius);
		writer->EndObject();
		return true;
	}
}