/*!*************************************************************************
****
\file EnemyIdle.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when enemy is idle.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyIdle.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyDamaged.h"

namespace EM
{
	EnemyIdle::EnemyIdle(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* EnemyIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is idle state
	****************************************************************************/
	void EnemyIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
	}

	/*!*************************************************************************
	Update state for when enemy is idle state
	****************************************************************************/
	void EnemyIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID()).SetNextPos(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos());
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		vec2D playerPos = vec2D();
		bool check = false;
		if (!check)
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				//std::cout << "Prox Check" << std::endl;
				if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
				{
					check = true;
					//std::cout << "Found Player" << std::endl;
					playerPos = p_ecs.GetComponent<Transform>(i).GetPos();

				}
			}
		}
		//if player moves within x radius, set mode to moving
		if (distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 0.4f && check) {
			//std::cout << "Player Detected" << std::endl;
			stateMachine->ChangeState(new EnemyChase(stateMachine));
		}

	}

	/*!*************************************************************************
	Exit state for when enemy is idle state
	****************************************************************************/
	void EnemyIdle::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}