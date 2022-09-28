#pragma once
#include "ComponentArray.h"
#include "Types.h"
#include "empch.h"

namespace EM
{
	class ComponentManager
	{
	public:
		template <typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

			// Add this component type to the component type map
			mComponentTypes.insert({ typeName, mNextComponentType });

			// Create a ComponentArray pointer and add it to the component arrays map
			mComponentArrays.insert({typename, std::make_shared<ComponentArray<T>>()});

			++mNextComponentType;
		}

		template <typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

			// Return this component's type - used for creating signatures
			return mComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(Entity entity, T Component)
		{
			// Add a component to the array for an entity
			// Serialize the Component here
			
		}

		template<typename T>
		void SerializeToBuild(Entity entity, T Component)
		{
			//Serialize all the data into file
		}

	private:

		// Map from type string pointer to a component type
		std::unordered_map<const char*, ComponentType> mComponentTypes{};

		// Map from type string pointer to a component array
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};

		//Initial component type id
		static const ComponentType mNextComponentType{};

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