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
#include "Components/Components.h"

namespace EM
{
	//Interface Class for ComponentArray

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;

		virtual void EntityDestroyed(Entity entity) = 0;

		virtual void CopyComponent(Entity entity, Entity entityToCopy) = 0;
		
		virtual std::array<size_t, MAX_ENTITIES>& GetEntityToIndexMap() = 0;

		virtual std::array<Entity, MAX_ENTITIES>& GetIndexToEntityMap() = 0;

		virtual const size_t GetEntitySize() = 0;

		virtual void ClearForWorldBuild() = 0;
		
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		inline ComponentArray()
		{
			std::fill(mEntityToIndexMap.begin(), mEntityToIndexMap.end(), MAX_ENTITIES);
			std::fill(mIndexToEntityMap.begin(), mIndexToEntityMap.end(), MAX_ENTITIES);
		}
		//To insert data into the map so that each entity is mapped to its index and vice versa
		//via std::unordered_map
		void InsertData(Entity entity, T component)
		{
			assert(mEntityToIndexMap[entity] == MAX_ENTITIES && "Component added to same entity more than once.");

			size_t newIndex = mSize;
			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;
			mComponentArray[newIndex] = component;
			component.entityID = entity;
			++mSize;
			EM_EXO_INFO("Size of m_size{0}", mSize);
		}

		//To remove data from the std::unordered_map and keep data packed within the array
		void RemoveData(Entity entity)
		{
			assert(mEntityToIndexMap[entity] != MAX_ENTITIES && "Removing non-existent component.");

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			// Update map to point to moved spot

			Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			mEntityToIndexMap[entity] = MAX_ENTITIES;
			mIndexToEntityMap[indexOfLastElement] = MAX_ENTITIES;

			--mSize;
			EM_EXO_INFO("Size of m_size{0}", mSize);
		}

		//Retrieves Data from the Component Array
		T& GetData(Entity entity)
		{
			//assert(mEntityToIndexMap[entity] != 0 && "Retrieving non-existent component.");

			// Return a reference to the entity's component
			return mComponentArray[mEntityToIndexMap[entity]];
		}

		//Checks if Component is attached to entity
		bool HaveComponent(Entity entity)
		{
			if (mEntityToIndexMap[entity] != MAX_ENTITIES)
			{
				return true;
			}
			return false;
		}

		//Ensure that the entity is destroyed and component data is removed
		void EntityDestroyed(Entity entity) override
		{
			if (mEntityToIndexMap[entity] != MAX_ENTITIES)
			{
				// Remove the entity's component if it existed
				RemoveData(entity);
				std::cout << "mf" << std::endl;
			}
		}

		void CopyComponent(Entity entity, Entity entityToCopy) override
		{
			T* CopyComponent = &mComponentArray[mEntityToIndexMap[entity]];
			T* CloneComponent = new T(*CopyComponent);
			InsertData(entityToCopy, *CloneComponent);
			//delete CloneComponent;
		}

		std::array<size_t, MAX_ENTITIES>& GetEntityToIndexMap()
		{
			return mEntityToIndexMap;
		}

		std::array<Entity, MAX_ENTITIES>& GetIndexToEntityMap()
		{
			return mIndexToEntityMap;
		}

		const size_t GetEntitySize()
		{
			return mSize;
		}

		void ClearForWorldBuild()
		{
			std::fill(mEntityToIndexMap.begin(), mEntityToIndexMap.end(), MAX_ENTITIES);
			std::fill(mIndexToEntityMap.begin(), mIndexToEntityMap.end(), MAX_ENTITIES);
		}

	private:

		std::array<T, MAX_ENTITIES> mComponentArray{};

		// Map from an entity ID to an array index.
		std::array<size_t, MAX_ENTITIES> mEntityToIndexMap;

		// Map from an array index to an entity ID.
		std::array<Entity, MAX_ENTITIES> mIndexToEntityMap;

		// Total size of valid entries in the array.
		size_t mSize = 0;
	};
}
