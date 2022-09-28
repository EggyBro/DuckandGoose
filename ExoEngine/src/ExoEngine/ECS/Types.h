#pragma once
#include "empch.h"

namespace EM
{
	//Alias for ID
	typedef std::uint32_t IDType;

	//Entity is simply an ID
	typedef IDType Entity;

	//Used to define the size of arrays, may use vector
	const Entity MAX_ENTITIES = 5000;

	//UniqueID used to identify Components
	typedef IDType ComponentType;

	//Used to define the size of component array
	const ComponentType MAX_COMPONENTS = 32;

	// 32 bit signature containing which component an entity has
	// The list of Components that an Entity has instances of based on the unique ID of the Signature.
	typedef std::bitset<MAX_COMPONENTS> Signature;
}