/*!*************************************************************************
****
\file LogicSystem.h
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

#pragma once
#include "Platform/System/System.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ECS/ECS.h"

namespace EM
{

	class LogicSystem : public System
	{
	public:
		/*!*************************************************************************
		Returns string name of system
		****************************************************************************/
		virtual std::string GetName() { return "LogicSystem"; }
		/*!*************************************************************************
		Initialize Logic System
		****************************************************************************/
		virtual void Init() override;
		/*!*************************************************************************
		Update Loop for Logic System
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for Logic System which will delete all script data
		****************************************************************************/
		virtual void End() override;
	};
}