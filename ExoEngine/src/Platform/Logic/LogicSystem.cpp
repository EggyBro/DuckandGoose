/*!*************************************************************************
****
\file LogicSystem.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Logic System used for iterating through each entity with a logic
component, grabbing the vector of scripts from the logic components and
iterating through each script to call its update functions

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "LogicSystem.h"
#include "ExoEngine/Timer/Time.h"

namespace EM
{
	/*!*************************************************************************
	Initialize Logic System
	****************************************************************************/
	void LogicSystem::Init()
	{
		/*auto mLogic = p_ecs.RegisterSystem<LogicSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Logic>());
			p_ecs.SetSystemSignature<LogicSystem>(signature);
		}*/
		for (const auto& entity : mEntities)
		{
			auto& LogicComp = p_ecs.GetComponent<Logic>(entity);
			for (auto i = LogicComp.GetScript().begin(); i != LogicComp.GetScript().end(); ++i)
			{
				if ((*i)->GetScriptEntityID() != entity)
				{
					LogicComp.SetScriptEntity(entity);
				}
				(*i)->Start();
			}
		}
	}

	/*!*************************************************************************
	Update Loop for Logic System
	****************************************************************************/
	void LogicSystem::Update(float Frametime)
	{
		Timer::GetInstance().Start(Systems::LOGIC);
		Timer::GetInstance().GetDT(Systems::LOGIC);
		for (const auto& entity : mEntities)
		{
			auto& LogicComp = p_ecs.GetComponent<Logic>(entity);
			for (auto i = LogicComp.GetScript().begin(); i != LogicComp.GetScript().end(); ++i)
			{
				if ((*i)->GetScriptEntityID() != entity)
				{
					LogicComp.SetScriptEntity(entity);
				}
				(*i)->Update(Frametime);
			}
		}
		Timer::GetInstance().Update(Systems::LOGIC);
	}

	/*!*************************************************************************
	End State for Logic System which will delete all script data
	****************************************************************************/
	void LogicSystem::End()
	{
		for (const auto& entity : mEntities)
		{
			auto& LogicComp = p_ecs.GetComponent<Logic>(entity);
			for (auto i = LogicComp.GetScript().begin(); i != LogicComp.GetScript().end(); ++i)
			{
				(*i)->End();
			}
		}
	}	
}