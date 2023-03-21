/*!*************************************************************************
****
\file On_Attack_1.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	1st attacking state for player

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "OnAttack_1.h"
#include "OnIdle.h"
#include "OnAttack_2.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnAttack_1::OnAttack_1(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* OnAttack_1::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key) && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown <= 0.0f)
		{
			return new OnBlock(stateMachine);
		}
		return nullptr;
	}
/*!*************************************************************************
	Enter state for Player Attack 1
****************************************************************************/
	void OnAttack_1::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer = 0.5f;
		}
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Normal_Attack_Swing1");
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
		}
	}

/*!*************************************************************************
	Update state for Player Attack 1
****************************************************************************/
	void OnAttack_1::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer -= Frametime;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown -= Frametime;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown -= Frametime;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown -= Frametime;
		}
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.2f)
			{
				stateMachine->ChangeState(new OnAttack_2(stateMachine));
			}
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
			{
				stateMachine->ChangeState(new OnDamaged(stateMachine));
			}
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.0f)
			{
				stateMachine->ChangeState(new OnIdle(stateMachine));
			}
		}
	}
/*!*************************************************************************
	Exit state for Player Attack 1
****************************************************************************/
	void OnAttack_1::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}