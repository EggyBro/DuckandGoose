/*!*****************************************************************************
\file PhysicsSystem.h
\author Tan Ek Hern, Lau Yong Hui
\par DP email: t.ekhern@digipen.edu, l.yonghui@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the system declaration for the physics system to update
		the entity's position. 
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#pragma once
#include "ExoEngine/Math/Physics.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
	class PhysicsSystem : public System
	{
	public:
		/*!*************************************************************************
		This function returns the purpose of the system as a flag for when it is called
		****************************************************************************/
		virtual std::string GetName() { return "Update Positions"; }
		/*!*************************************************************************
		This function initialises the system. As there are no data members that require
		initialization, this function is empty
		****************************************************************************/
		virtual void Init() override;
		/*!*************************************************************************
		This function runs the logics of the system to update the entity positions
		by setting the current position as the entity's next position which has been 
		calculated previously
		****************************************************************************/
		virtual void Update();
		/*!*************************************************************************
		This function ends the system. As there are no data members that require
		initialization, there are no data members that need to be un-initialised. 
		Therefore this function is empty
		****************************************************************************/
		void End();
	private:
    };
}