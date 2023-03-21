/*!*************************************************************************
****
\file EnemyAttributes.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic the enemy attributes component of the game.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyAttributes.h"

namespace EM
{
	EnemyAttributes::EnemyAttributes() : mHealth{ 100 }, mMaxHealth{ 100 }, mDamage{ 10 }, mAttackTimer{ 1.0f }, mAttackCoolDown{ 0.0f }, mDamageCoolDownTimer{ 2.0f }, mDamageDurationTimer{ 0.0f }, mIsAlive{ false }, mIsDamaged{ false }, mEnemyType{EnemyTypes::ENEMY_NONE}, mVel{ vec2D(1.0f,1.0f) } {}

	/*!*************************************************************************
	Deserialize attributes
	****************************************************************************/
	bool EnemyAttributes::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		mMaxHealth = obj["Max Health"].GetInt();
		mDamage = obj["Damage"].GetInt();
		mEnemyType = static_cast<EnemyTypes>(obj["EnemyType"].GetInt());
		//mAttackTimer = (float)obj["Attack Timer"].GetDouble();
		//mDamageCooldownTimer = (float)obj["Damage Cooldown"].GetDouble();
		return true;
	}

	/*!*************************************************************************
	Deserialize attributes
	****************************************************************************/
	bool EnemyAttributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->Key("Max Health");
		writer->Int(mMaxHealth);
		writer->Key("Damage");
		writer->Int(mDamage);
		writer->Key("EnemyType");
		writer->Int(static_cast<int>(mEnemyType));
		//writer->Key("Attack Timer");
		//writer->Double((double)mAttackTimer);
		//writer->Key("Damage Cooldown");
		//writer->Double((double)mDamageCooldownTimer);
		//writer->EndObject();
		return true;
	}
}