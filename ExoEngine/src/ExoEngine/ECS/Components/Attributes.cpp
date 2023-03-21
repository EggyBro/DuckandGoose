/*!*************************************************************************
****
\file Attributes.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic the attributes component of the game.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Attributes.h"

namespace EM
{
	Attributes::Attributes() : mFiringCoolDown{ 2.0f }, mFireDurationTimer{ 1.0f }, mChargeCoolDown{ 2.0f }, mHazardDmg{ 20 }, mHazardType{HazardTypes::HAZARD_EMPTY} {}

	/*!*************************************************************************
	Deserialize attributes
	****************************************************************************/
	bool Attributes::Deserialize(const rapidjson::Value& obj)
	{
		mFiringCoolDown = obj["FiringCooldown"].GetFloat();
		mFireDurationTimer = obj["FiringDuration"].GetFloat();
		mChargeCoolDown = obj["ChargeDuration"].GetFloat();
		mHazardDmg = obj["HazardDamage"].GetInt();
		mHazardType = static_cast<Attributes::HazardTypes>(obj["HazardType"].GetInt());
		return true;
	}

	/*!*************************************************************************
	Serialize attributes
	****************************************************************************/
	bool Attributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("FiringCooldown");
		writer->Double(mFiringCoolDown);
		writer->Key("FiringDuration");
		writer->Double(mFireDurationTimer);
		writer->Key("ChargeDuration");
		writer->Double(mChargeCoolDown);
		writer->Key("HazardDamage");
		writer->Int(mHazardDmg);
		writer->Key("HazardType");
		writer->Int(static_cast<int>(mHazardType));
		//writer->EndObject();
		return true;
	}
}