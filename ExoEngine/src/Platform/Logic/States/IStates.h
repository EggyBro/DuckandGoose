/*!*************************************************************************
****
\file IState.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the implementation of abstract classes for creating all states

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "empch.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/ECS/ECS.h"
#include "Platform/Logic/StateMachines/StateMachine.h"

namespace EM
{
	class StateMachine;

	class IStates
	{
	public:
		virtual ~IStates() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) = 0;
		virtual void OnEnter(StateMachine* stateMachine) = 0;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) = 0;
		virtual void OnExit(StateMachine* stateMachine) = 0;
	};

}