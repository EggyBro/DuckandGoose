/*!*****************************************************************************
\file PhysicsSystem.cpp
\author Tan Ek Hern, Lau Yong Hui
\par DP email: t.ekhern@digipen.edu, l.yonghui@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the function definitions for the physics system
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "PhysicsSystem.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	/*!*************************************************************************
	This function initialises the system. As there are no data members that require
	initialization, this function is empty
	****************************************************************************/
	void PhysicsSystem::Init() {}
	/*!*************************************************************************
	This function runs the logics of the system to update the entity positions
	by setting the current position as the entity's next position which has been 
	calculated previously
	****************************************************************************/
	void PhysicsSystem::Update()
	{
		Timer::GetInstance().Start(Systems::PHYSICS);
		Timer::GetInstance().GetDT(Systems::PHYSICS);
		for (const auto& entity : mEntities)
		{
			auto& mTrans = p_ecs.GetComponent<Transform>(entity);
			auto& mRigid = p_ecs.GetComponent<RigidBody>(entity);

			if (entity == mTrans.GetComponentEntityID())
			{
				mTrans.SetPos(mRigid.GetNextPos());
			}
			else
			{
				mTrans.SetPos(p_ecs.GetComponent<RigidBody>(mTrans.GetComponentEntityID()).GetNextPos());
			}
		}
		Timer::GetInstance().Update(Systems::PHYSICS);
	}
	/*!*************************************************************************
	This function ends the system. As there are no data members that require
	initialization, there are no data members that need to be un-initialised. 
	Therefore this function is empty
	****************************************************************************/
	void PhysicsSystem::End() {}
}