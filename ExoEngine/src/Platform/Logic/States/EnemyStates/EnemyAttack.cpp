/*!*************************************************************************
****
\file EnemyAttack.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the enemy attack state

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyAttack.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyIdle.h"
#include "EnemyDamaged.h"
#include "EnemyTransition.h"

namespace EM
{
	EnemyAttack::EnemyAttack(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* EnemyAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine);
		UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for enemy attacking state
	****************************************************************************/
	void EnemyAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer = 1.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_ENEMY_MELEE_ATTACKING_SPRITESHEET");
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for enemy attacking state
	****************************************************************************/
	void EnemyAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.7f)
		{
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		}
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f)
		{
			stateMachine->ChangeState(new EnemyTransition(stateMachine));
		}
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
	}

	/*!*************************************************************************
	Exit state for enemy attacking state
	****************************************************************************/
	void EnemyAttack::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}