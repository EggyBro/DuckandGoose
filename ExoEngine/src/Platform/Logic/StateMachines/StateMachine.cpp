/*!*************************************************************************
****
\file StateMachine.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the games state machine

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "StateMachine.h"
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	StateMachine::StateMachine(Entity entity) : mCurrState{}, mEntityID{ entity } {}

	/*PlayerStates* GetCurrState()
	{
		return mCurrState;
	}*/
	
	void StateMachine::ChangeState(IStates* pNewState)
	{
		if (mCurrState != nullptr)
		{
			mCurrState->OnExit(this);
		}
		mCurrState = pNewState;
		mCurrState->OnEnter(this);
	}

	void StateMachine::HandleInput(const int& key)
	{
		IStates* state = mCurrState->HandleInput(this, key);
		if (state != nullptr)
		{
			ChangeState(state);
		}
		 
	}

	const Entity& StateMachine::GetEntityID()
	{
		return mEntityID;
	}

	void StateMachine::OnUpdate(float Frametime)
	{
		mCurrState->OnUpdate(this, Frametime);
	}
}