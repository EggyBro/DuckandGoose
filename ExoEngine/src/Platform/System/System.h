/*!*************************************************************************
****
\file System.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  Interface class for Systems to be used to create additional systems
****************************************************************************
***/

#pragma once
#include "ExoEngine/Core.h"
#include "ExoEngine/ECS/Types.h"

namespace EM {

	class EM_API System
	{
	public:
		std::set<Entity> mEntities;
		virtual std::string GetName() = 0;
		virtual ~System() {};
		//System function
		virtual void Init() = 0 {};
		virtual void Update() = 0 {};
		virtual void End() = 0 {};

	protected:
		std::string m_DebugName;

	};
}