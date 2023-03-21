/*!*************************************************************************
****
\file EnemyDamaged.cpp
\author Elton Teo Zhe Wei, Cheung Jun Yin Matthew
\par DP email: e.teo@digipen.edu, j.cheung@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when enemy is damaged.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyDamaged.h"
#include "EnemyDeath.h"
#include "EnemyChase.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDamaged::EnemyDamaged(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* EnemyDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is damaged state
	****************************************************************************/
	void EnemyDamaged::OnEnter(StateMachine* stateMachine)
	{
		//std::cout << "Enemy Damaged\n";
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player") {
				pDmg = p_ecs.GetComponent<PlayerAttributes>(i).mDamage;
			}
		}
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 0.5f;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Enemy_Damaged_Normal_Attack");

		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 1))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[1].should_play = true;
		}
		/*if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
		{
			stateMachine->ChangeState(new EnemyDeath(stateMachine));
		}*/
	}

	/*!*************************************************************************
	Update state for when enemy is damaged state
	****************************************************************************/
	void EnemyDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0) {
			if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
			{
				stateMachine->ChangeState(new EnemyDeath(stateMachine));
			}
			else
			{
				stateMachine->ChangeState(new EnemyChase(stateMachine));
			}
		}
	}

	/*!*************************************************************************
	Exit state for when enemy is damaged state
	****************************************************************************/
	void EnemyDamaged::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged = false;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}