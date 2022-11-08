/*!*************************************************************************
****
\file ECS.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains the coordinator for the three systems in place
that manages the ECS, the component, entity and system manager communicates
with each other using this class
****************************************************************************
***/

#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "Platform/System/SystemManager.h"
#include "Types.h"
#include "empch.h"

#define p_ecs EM::ECS::GetInstance()

namespace EM
{
	class ECS
	{
	public:

		static ECS& GetInstance()
		{
			static ECS instance;
			return instance;
		}

		void Init()
		{
			mComponentManager = std::make_unique<ComponentManager>();
			mEntityManager = std::make_unique<EntityManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		// Entity methods
		Entity CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			mEntityManager->DestroyEntity(entity);
			mComponentManager->EntityDestroyed(entity);
			mSystemManager->EntityDestroyed(entity);
		}

		Entity CloneEntity(Entity entity)
		{
			Entity newEntity = mEntityManager->CreateEntity();
			mEntityManager->SetSignature(newEntity, GetEntitySignature(entity));
			for (ComponentType i = 0; i < GetTotalRegisteredComponents(); ++i)
			{
				if (GetEntitySignature(newEntity).test(i))
				{
					mComponentManager->GetComponentArrayFromType(i)->CopyComponent(entity, newEntity);
				}
			}
			auto signature = mEntityManager->GetSignature(newEntity);
			mSystemManager->EntitySignatureChanged(newEntity, signature);

			return newEntity;
		}

		Signature GetEntitySignature(Entity entity)
		{
			return mEntityManager->GetSignature(entity);
		}

		void SetEntitySignature(Entity entity, Signature signature)
		{
			mEntityManager->SetSignature(entity, signature);
		}

		Entity GetTotalEntities()
		{
			return mEntityManager->GetTotalEntities();
		}

		void SetTotalEntitiesForWorldBuild(Entity entity)
		{
			mEntityManager->SetTotalEntitiesForWorld(entity);
		}

		void ResetEntities()
		{
			mEntityManager->ResetEntities();
		}

		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);
			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		void AddComponentsSignature(Entity entity, Signature signature)
		{
			if (signature.test(GetComponentType<Transform>()))
			{
				Transform transform;
				AddComponent<Transform>(entity, transform);
			}
			if (signature.test(GetComponentType<RigidBody>()))
			{
				RigidBody rigidbody;
				AddComponent<RigidBody>(entity, rigidbody);
			}
			if (signature.test(GetComponentType<Sprite>()))
			{
				Sprite sprite;
				AddComponent<Sprite>(entity, sprite);
			}
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			mComponentManager->RemoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return mComponentManager->GetComponentType<T>();
		}

		std::string GetComponentTypeName(ComponentType Type)
		{
			return mComponentManager->GetComponentTypeName(Type);
		}

		template<typename T>
		bool HaveComponent(Entity entity)
		{
			return mComponentManager->HaveComponent<T>(entity);
		}

		std::array<size_t, MAX_ENTITIES>& GetEntityToIndexMapECS(ComponentType Type)
		{
			return mComponentManager->GetEntityToIndexMap(Type);
		}

		std::array<Entity, MAX_ENTITIES>& GetIndexToEntityMapECS(ComponentType Type)
		{
			return mComponentManager->GetIndexToEntityMap(Type);
		}

		const ComponentType GetTotalRegisteredComponents()
		{
			return mComponentManager->GetTotalRegisteredComponents();
		}

		const size_t GetEntitySize(ComponentType Type)
		{
			return mComponentManager->GetEntitySize(Type);
		}

		void ClearArrayForWorldBuild(ComponentType Type)
		{
			return mComponentManager->ClearArrayForWorldBuild(Type);
		}

		std::shared_ptr<IComponentArray> GetComponentArrayFromType(ComponentType Type)
		{
			return mComponentManager->GetComponentArrayFromType(Type);
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return mSystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			mSystemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystemManager;
		inline static std::unique_ptr<ECS> m_instance;
	};
}
