/*!*************************************************************************
****
\file StateMachine.h
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
#pragma once
#include "empch.h"
#include "ExoEngine/ECS/Types.h"

namespace EM
{
	class IStates;

	class StateMachine
	{
	public:
		StateMachine(Entity entity);

		~StateMachine() = default;

		//PlayerStates* GetCurrState();

		void ChangeState(IStates* pNewState);

		void HandleInput(const int& key);

		const Entity& GetEntityID();

		void SetEntityID(Entity& entity) { mEntityID = entity; }

		void OnUpdate(float Frametime);

	private:
		IStates* mCurrState;
		Entity mEntityID;
	};
}