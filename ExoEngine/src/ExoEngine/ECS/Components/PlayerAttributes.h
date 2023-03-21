/*!*************************************************************************
****
\file PlayerAttributes.h
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
#pragma once
#include "IComponent.h"
#include "empch.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class PlayerAttributes : public IComponent
	{
	public:
		PlayerAttributes();
		~PlayerAttributes() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	public:
		int mHealth;
		int mMaxHealth;
		int mDamage;
		int mAttackCounter;
		float mDamageCoolDown;
		float mDashCoolDown;
		float mDashDurationTimer;
		float mBlockCoolDown;	//5.0f
		float mBlockDurationTimer;
		float mCooldownTimer;
		float mDamageTaken;
		float mDamageDurationTimer;
		bool mIsDamaged;
		bool mIsBlocking;
		bool mIsDashing;
		vec2D mVel;
		vec2D mDir;
		entityPhysics mPhys;
	};
}