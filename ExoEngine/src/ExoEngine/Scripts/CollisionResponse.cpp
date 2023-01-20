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
	void CollisionResponse::Start() {}
	/*!*************************************************************************
	This function runs the logic of the script to check for collision and apply
    a counter-force to the entity's current velocity which is calculated based on
    the current velocity and the collision normal
	****************************************************************************/
	void CollisionResponse::Update(float Frametime)
	{
		if (Frametime) {

		}
        auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
		auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		if (col.GetAlive() && col.GetHit()) {
			std::cout << "Current velocity: " << rigidbody.GetVel().x << ", " << rigidbody.GetVel().y << "\n";
			vec2D response = rigidbody.GetVel();
			vec2D normal = col.GetNormal();
			float dotProd = dotProduct(normal, response);
			if (dotProd <= 0) {
				normal = normal * dotProd;
				response -= normal;
				rigidbody.SetVel(response);
			}
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			rigidbody.SetNextPos(nextPos);

			if (tag.GetNameTag() == "Player")
			{
				logic.GetScript()[0]->Update(Frametime);
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