#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystEMManager.h"
#include "Types.h"
#include "empch.h"

namespace EM
{
	class ECS
	{
	public:
		void Init()
		{
			mComponentManager = std::make_unique<ComponentManager>();
			mEntityManager = std::make_unique<EntityManager>();
			mSystEMManager = std::make_unique<SystemManager>();
		}


		// Entity methods
		EntityID CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}

		void DestroyEntity(EntityID entity)
		{
			mEntityManager->DestroyEntity(entity);

			mComponentManager->EntityDestroyed(entity);

			mSystEMManager->EntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystEMManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void REMoveComponent(EntityID entity)
		{
			mComponentManager->REMoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystEMManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentTypeID GetComponentType()
		{
			return mComponentManager->GetComponentType<T>();
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystEM()
		{
			return mSystEMManager->RegisterSystEM<T>();
		}

		template<typename T>
		void SetSystEMSignature(SignatureID signature)
		{
			mSystEMManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystEMManager;
	};
}
