/*!*************************************************************************
****
\file EnemyChase.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the enemy chasing state

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyChase.h"
#include "EnemyAttack.h"
#include "EnemyDeath.h"
#include "EnemyDamaged.h"
#include "EnemyIdle.h"

namespace EM
{
	EnemyChase::EnemyChase(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* EnemyChase::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is chasing state
	****************************************************************************/
	void EnemyChase::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
	}

	/*!*************************************************************************
	Update state for when enemy is chasing state
	****************************************************************************/
	void EnemyChase::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		float dist = 0;
		vec2D playerPos = vec2D();
		bool check = false;
		auto& transform = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
		if (!check)
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
				{
					playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
					check = true;
					//std::cout << "Player Detected\n";
				}
			}
		}
		if (check) {
			rigidbody.SetDir(transform.GetPos().x - playerPos.x, transform.GetPos().y - playerPos.y);
			vec2D newVel = vec2D(0.0f, 0.0f);
			newVel = rigidbody.GetVel();
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetUVCoor().x = 512.0f;
			newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
			newVel = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
			if (newVel.x > -99 && newVel.y < 99) {
				newVel = newVel * -1;
				rigidbody.SetVel(newVel);
				if (newVel.x < 0 && transform.GetScale().x < 0) {
					transform.GetScale().x *= -1;
				}
				if (newVel.x > 0 && transform.GetScale().x > 0) {
					transform.GetScale().x *= -1;
				}
			}
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			rigidbody.SetNextPos(nextPos);
			//std::cout << "Curr Pos: " << transform.GetPos().x << ", " << transform.GetPos().y << std::endl;
			//std::cout << "Next Pos: " << nextPos.x << ", " << nextPos.y << std::endl;
			//std::cout << "Actual Next Pos: " << rigidbody.GetNextPos().x << ", " << rigidbody.GetNextPos().y << std::endl;
			dist = distance(transform.GetPos(), playerPos);
			//______________________________________BODGE FIX. REMOVE AFTER FIXING RIGIDBODY____________________________________
			//transform.SetPos(nextPos);
			//__________________________________________________________________________________________________________________
			//Attack Range
			//check if within range. If not, set to moving state
			if (dist < 0.15f && p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f)
			{
				//std::cout << "In Proximity2" << std::endl;
				//if within range to attack, set mode to attacking
				stateMachine->ChangeState(new EnemyAttack(stateMachine));
			}
		}
	}

	/*!*************************************************************************
	Exit state for when enemy is chasing state
	****************************************************************************/
	void EnemyChase::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}