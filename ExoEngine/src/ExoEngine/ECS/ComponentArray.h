/*!*************************************************************************
****
\file ComponentArray.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains a templated class for storing an array of
components based on the type. This templated class is used for an ECS to map
each entity to index and each index to entity to ensure a packed array of
components

****************************************************************************
***/
#pragma once
#include "Types.h"
#include "empch.h"
#include "Components.h"

namespace EM
{
	//Interface Class for ComponentArray
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;

		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		//To insert data into the map so that each entity is mapped to its index and vice versa
		//via std::unordered_map
		void InsertData(Entity entity, T component)
		{
			assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

			size_t newIndex = mSize;
			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;
			mComponentArray[newIndex] = component;
			++mSize;
		}

		//To remove data from the std::unordered_map and keep data packed within the array
		void RemoveData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			// Update map to point to moved spot
			Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);

			--mSize;
		}

		//Retrieves Data from the Component Array
		T& GetData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

			// Return a reference to the entity's component
			return mComponentArray[mEntityToIndexMap[entity]];
		}

		//Ensure that the entity is destroyed and component data is removed
		void EntityDestroyed(Entity entity) override
		{
			if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				RemoveData(entity);
			}
		}

	private:

		std::vector<T> mComponentArray {MAX_ENTITIES};

		// Map from an entity ID to an array index.
		std::unordered_map<Entity, size_t> mEntityToIndexMap;

		// Map from an array index to an entity ID.
		std::unordered_map<size_t, Entity> mIndexToEntityMap;

		// Total size of valid entries in the array.
		size_t mSize;
	};
}
