/*!*****************************************************************************
\file CollisionSystem.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the system declaration for the collision system to
        detect collision between two entities and calculate the appropriate physics
        response
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#pragma once
#include "ExoEngine/Math/Physics.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
    class CollisionSystem : public System {
    public:
        /*!*************************************************************************
		This function returns the purpose of the system as a flag for when it is called
		****************************************************************************/
        virtual std::string GetName() { return "Collision"; }
        /*!*************************************************************************
		This function initialises the system. As there are no data members that require
		initialization, this function is empty
		****************************************************************************/
        virtual void Init() override;
        /*!*************************************************************************
		This function runs the logic of the system. It checks the list of entities with
        a collision component in pairs to see which of them are colliding. If two objects
        are colliding, collision response is dictated by the type of collider the object
        has
		****************************************************************************/
        virtual void Update(float dt) override;
        /*!*************************************************************************
		This function ends the system. As there are no data members that require
		initialization, there are no data members that need to be un-initialised. 
		Therefore this function is empty
		****************************************************************************/
        virtual void End() override;
    private:
        entityCollision ecm;
    };
}