/*!*************************************************************************
****
\file RigidBody.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  RigidBody Component to describe material of object and the forces
acting on said object.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "RigidBody.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for RigidBody Component
	****************************************************************************/
	RigidBody::RigidBody() : mAccel{vec2D(0.f,0.f)}, mVelocity{vec2D(1.0f,1.0f)}, mDirection{vec2D(1.0f,0.0f)}, mFriction{0.0f}, mRestitution{0.0f} {}

	/*!*************************************************************************
	Deserialize for RigidBody
	****************************************************************************/
	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		mAccel = vec2D(obj["velX"].GetFloat(), obj["velY"].GetFloat());
		mDirection = vec2D(obj["dirX"].GetFloat(), obj["dirY"].GetFloat());
		mFriction = obj["Friction"].GetFloat();
		mRestitution = obj["Restitution"].GetFloat();
		return true;
	}

	/*!*************************************************************************
	Serialize for RigidBody
	****************************************************************************/
	bool RigidBody::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("velX");
		writer->Double(mAccel.x);
		writer->Key("velY");
		writer->Double(mAccel.y);
		writer->Key("dirX");
		writer->Double(mDirection.x);
		writer->Key("dirY");
		writer->Double(mDirection.y);
		writer->Key("Friction");
		writer->Double(mFriction);
		writer->Key("Restitution");
		writer->Double(mRestitution);
		//writer->EndObject();
		return true;
	}
	//End RigidBody
}