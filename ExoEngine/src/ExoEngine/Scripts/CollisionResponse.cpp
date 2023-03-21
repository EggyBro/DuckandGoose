/*!*****************************************************************************
\file CollisionResponse.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 27-11-2022
\brief  This file contains the function definitions for the collision response
		script
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "CollisionResponse.h"
#include "SkillsChest.h"
#include "ExoEngine/ECS/SceneManager.h"

namespace EM
{
	/*!*************************************************************************
	This function clones the script by allocating and constructing a copy of this 
	script and returning it
	****************************************************************************/
	CollisionResponse* CollisionResponse::Clone() const
	{
		 return new CollisionResponse(*this);
	}
	/*!*************************************************************************
	This function initialises the script. As there are no data members that require
	initialization, this function is empty
	****************************************************************************/
	void CollisionResponse::Start() 
	{
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<EnemyAttributes>(i))
			{
				++mTotalEnemies;
			}
		}
	}
	/*!*************************************************************************
	This function runs the logic of the script to check for collision and apply
    a counter-force to the entity's current velocity which is calculated based on
    the current velocity and the collision normal
	****************************************************************************/
	void CollisionResponse::Update(float Frametime)
	{
		UNREFERENCED_PARAMETER(Frametime);
		if (p_ecs.HaveComponent<Collider>(GetScriptEntityID())) {
			auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());

			//Taking Damage As Player
			if (p_ecs.HaveComponent<Tag>(GetScriptEntityID()) && p_ecs.GetComponent<Tag>(GetScriptEntityID()).GetTag() == "Player")
			{
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<EnemyAttributes>(i) || p_ecs.HaveComponent<Attributes>(i))
					{
						if (p_ecs.GetComponent<Collider>(i).GetCollisionArray()[1].is_Alive)
						{
							if (col.GetCollisionArray()[0].mHit == 2)
							{
								auto& playerstats = p_ecs.GetComponent<PlayerAttributes>(GetScriptEntityID());
								if (playerstats.mDamageCoolDown <= 0.0f)
								{
									playerstats.mIsDamaged = true;
								}
							}
						}
					}
				}
			}
			//Enemy Taking Damage
			if (p_ecs.HaveComponent<Tag>(GetScriptEntityID()) && p_ecs.GetComponent<Tag>(GetScriptEntityID()).GetTag() == "Enemy")
			{
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<PlayerAttributes>(i))
					{
						if (p_ecs.GetComponent<Collider>(i).GetCollisionArray()[1].is_Alive)
						{
							if (col.GetCollisionArray()[0].mHit == 2)
							{
								auto& enemystats = p_ecs.GetComponent<EnemyAttributes>(GetScriptEntityID());
								if (enemystats.mDamageCoolDownTimer <= 0.0f)
								{
									enemystats.mIsDamaged = true;
								}
							}
						}
					}
				}
			}

			if (p_ecs.HaveComponent<Tag>(GetScriptEntityID()) && p_ecs.GetComponent<Tag>(GetScriptEntityID()).GetTag() == "Player")
			{
				mTotalDeadEnemies = 0;
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<EnemyAttributes>(i))
					{
						if (p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive == false && p_ecs.GetComponent<EnemyAttributes>(i).mHealth <= 0.0f)
						{
							++mTotalDeadEnemies;
						}
					}
					if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Win" && (mTotalDeadEnemies == mTotalEnemies))
					{
						p_ecs.GetComponent<Collider>(i).GetCollisionArray()[0].is_Alive = true;
						p_ecs.GetComponent<Collider>(i).GetCollisionArray()[1].is_Alive = true;
						if (col.GetCollisionArray()[0].mHit == 2 && p_ecs.GetComponent<Collider>(i).GetCollisionArray()[0].mHit == 4)
						{
							p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
						}
					}
				}
			}
		}
		
	}
	/*!*************************************************************************
	This function ends the script by deleting the pointer to this script
	****************************************************************************/
	void CollisionResponse::End()
	{
		delete this;
	}
	/*!*************************************************************************
	This function returns the purpose of the script as a flag for when it is called
	****************************************************************************/
	std::string CollisionResponse::GetScriptName() { return "CollisionResponse"; }
}