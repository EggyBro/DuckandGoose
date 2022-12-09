/*!*************************************************************************
****
\file Types.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  Typedefs for various data types to be used in the ECS
****************************************************************************
***/

#pragma once
#include "empch.h"

namespace EM
{
	// Alias for ID
	typedef std::uint32_t IDType;

	// Entity is simply an ID
	typedef IDType Entity;

	// Used to define the size of arrays, may use vector
	const Entity MAX_ENTITIES = 100; //Limit 800

	// UniqueID used to identify Components
	typedef IDType ComponentType;

	// Used to define the size of component array
	const ComponentType MAX_COMPONENTS = 32;

	// 32 bit signature containing which component an entity has
	// The list of Components that an Entity has instances of based on the unique ID of the Signature.
	typedef std::bitset<MAX_COMPONENTS> Signature;
}