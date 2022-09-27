#pragma once

#include "empch.h"

namespace EM
{
	//Alias for ID
	typedef std::uint32_t IDType;

	//Entity is simply an ID
	typedef IDType EntityID;

	//Used to define the size of arrays, may use vector
	const EntityID MAX_ENTITIES = 5000;

	//UniqueID used to group identify Components
	typedef IDType ComponentTypeID;

	//Used to define the size of component array
	const ComponentTypeID MAX_COMPONENTS = 32;

	//Represents the ArcheType/Signature and what components it can handle
	//The list of Components that an Entity has instances of.
	typedef std::bitset<MAX_COMPONENTS> SignatureID;

	class SystEM
	{
	public:
		std::set<EntityID> mEntities;
	};
}