/*!*************************************************************************
****
\file ComponentManager.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains a templated class for communicating with all
Component Arrays and allowing for different components to be registerd to
the ECS. Registered components can then be added to various systems and
entities within the ECS. The system will then have a unique signature based
on components added and will update all components belonging to the system

****************************************************************************
***/

#pragma once
#include "ComponentArray.h"
#include "Types.h"
#include "empch.h"
#include "Components/Components.h"

namespace EM
{
	class ComponentManager
	{
	public:
		//Registers Components for use within the ECS
		template <typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

			auto CompArray = std::make_shared<ComponentArray<T>>();

			// Add this component type to the component type map
			mComponentTypes.insert({ typeName, mNextComponentType });

			// Create a ComponentArray pointer and add it to the component arrays map
			mComponentArrays.insert({ typeName, CompArray });

			ComponentType cType = mComponentTypes[typeName];

			mComponentArraysFromType.try_emplace( cType , CompArray );

			++mNextComponentType;

			++ComponentsRegistered;
		}

		//Returns the ComponentType;
		template <typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

			// Return this component's type - used for creating signatures
			return mComponentTypes[typeName];
		}

		std::string GetComponentTypeName(ComponentType Type)
		{
			std::string TypeName;
			for (std::unordered_map<const char*, ComponentType>::const_iterator it = mComponentTypes.begin(); it != mComponentTypes.end(); ++it) 
			{
				if (it->second == Type)
				{
					TypeName = it->first;
				}
			}
			TypeName = TypeName.substr(TypeName.find_first_of("::") + 2, TypeName.length());
			return TypeName;
		}

		//Add Components to the ComponentArray
		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			// Add a component to the array for an entity
			GetComponentArray<T>()->InsertData(entity, component);
		}

		//Remove Components to the ComponentArray
		template<typename T>
		void RemoveComponent(Entity entity)
		{
			// Remove a component from the array for an entity
			GetComponentArray<T>()->RemoveData(entity);
		}

		//Retrieve Component Data from the Respective ComponentArray
		template<typename T>
		T& GetComponent(Entity entity)
		{
			// Get a reference to a component from the array for an entity
			return GetComponentArray<T>()->GetData(entity);
		}


		template<typename T>
		bool HaveComponent(Entity entity)
		{
			return GetComponentArray<T>()->HaveComponent(entity);
		}

		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mComponentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

		std::array<size_t, MAX_ENTITIES>& GetEntityToIndexMap(ComponentType Type)
		{
			return GetComponentArrayFromType(Type)->GetEntityToIndexMap();
		}

		std::array<Entity, MAX_ENTITIES>& GetIndexToEntityMap(ComponentType Type)
		{
			return GetComponentArrayFromType(Type)->GetIndexToEntityMap();
		}

		const ComponentType GetTotalRegisteredComponents()
		{
			return ComponentsRegistered;
		}

		const size_t GetEntitySize(ComponentType Type)
		{
			return GetComponentArrayFromType(Type)->GetEntitySize();
		}

		void ClearArrayForWorldBuild(ComponentType Type)
		{
			GetComponentArrayFromType(Type)->ClearForWorldBuild();
		}

		inline std::shared_ptr<IComponentArray> GetComponentArrayFromType(ComponentType Type)
		{
			return mComponentArraysFromType[Type];
		}

	private:

		inline static ComponentType ComponentsRegistered{};

		// Map from type string pointer to a component type
		std::unordered_map<const char*, ComponentType> mComponentTypes{};

		// Map from type string pointer to a component array
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

		std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> mComponentArraysFromType{};

		//Initial component type id
		ComponentType mNextComponentType{};

		// Convenience function to get the statically casted pointer to the ComponentArray of type T.
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
		}

	};
}