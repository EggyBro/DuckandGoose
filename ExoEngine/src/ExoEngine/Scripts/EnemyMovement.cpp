/*!*************************************************************************
****
\file EnemyMovement.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for basic pathfinding for Enemy Movement will be expanded
for more complex pathfinding

****************************************************************************
***/
#include "empch.h"
#include "EnemyMovement.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for new Enemy Movement Scripts
	****************************************************************************/
	EnemyMovement::EnemyMovement() : mAttackCooldown{ 0.0f }, mAttackTime{0.0f} {};

	/*!*************************************************************************
	returns an instance for a new Enemy Movement Script
	****************************************************************************/
	EnemyMovement* EnemyMovement::Clone() const
	{
		return new EnemyMovement(*this);
	}

	/*!*************************************************************************
	Init for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Start() {}

	/*!*************************************************************************
	Update loop for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Update(float Frametime)
	{
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && !std::strcmp(p_ecs.GetComponent<Tag>(i).GetTag().c_str(), "Player"))
			{
				rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
			}
		}
		vec2D newVel = vec2D(0,0);
		newVel = rigidbody.GetVel();
		if (mAttackCooldown <= 0.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeIdle");
		}
		if (squarelength(rigidbody.GetDir()) < 3.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeRunning");
			newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
			newVel = mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
			//Attack Range
			if (squarelength(rigidbody.GetDir()) < 0.1f)
			{
				//Attack Logic Here
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeAttack");
				if (mAttackTime > 0.0f)
				{
					mAttackCooldown = 2.5f;
				}
				if (mAttackCooldown <= 0.0f)
				{
					mAttackTime = 1.0f;
				}
			}
		}
		if (mAttackCooldown > 0.0f && mAttackTime <= 0.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeRunning");
			newVel -= newVel * 2;
		}
		else {
			newVel = (mPhys.friction(newVel, Frametime));
		}
		if (newVel.x > -99 && newVel.y < 99) {
			rigidbody.SetVel(newVel);
		}
		vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
		rigidbody.SetNextPos(nextPos);
		mAttackCooldown -= Frametime;
		mAttackTime -= Frametime;
	}

	/*!*************************************************************************
	End of Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::End() 
	{
		delete this;
	}

	/*!*************************************************************************
	Returns the name of the script
	****************************************************************************/
	std::string EnemyMovement::GetScriptName() { return "EnemyMovement"; }
}