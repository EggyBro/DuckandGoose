/*!*************************************************************************
****
\file PlayerAttributes.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic the player attributes component of the game.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "PlayerAttributes.h"

namespace EM
{
	PlayerAttributes::PlayerAttributes() : mHealth{ 100 }, mMaxHealth{ 100 }, mDamage{ 20 }, mAttackCounter{ 0 }, mDamageCoolDown{ 0.0f }, mDashCoolDown{ 0.0f },
		mDashDurationTimer{ 0.2f }, mBlockCoolDown{ 0.0f }, mBlockDurationTimer{ 2.0f }, mCooldownTimer{ 0.5f }, mDamageTaken{ 0.0f }, mDamageDurationTimer{ 0.5f }, mIsDamaged{ false },
		mIsBlocking{ false }, mIsDashing{ false }, mVel{ vec2D(1.0f,1.0f) }, mDir{ vec2D(1.0f,0.0f) } {}

	/*!*************************************************************************
	Deserialize attributes
	****************************************************************************/
	bool PlayerAttributes::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		mMaxHealth = obj["Max Health"].GetInt();
		mDamage = obj["Damage"].GetInt();
		return true;
	}

	/*!*************************************************************************
	Serialize attributes
	****************************************************************************/
	bool PlayerAttributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->Key("Max Health");
		writer->Int(mMaxHealth);
		writer->Key("Damage");
		writer->Int(mDamage);
		//writer->EndObject();
		return true;
	}
}