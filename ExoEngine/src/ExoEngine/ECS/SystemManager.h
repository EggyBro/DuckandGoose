#pragma once

#include "Types.h"
#include "empch.h"
#include "../Core.h"

namespace EM
{
	class EM_API SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(SignatureID signature)
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

			mSignatures.insert({ typeName, signature });
		}

		void EntityDestroyed(EntityID entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;


				system->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(EntityID entity, SignatureID entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = mSignatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->mEntities.insert(entity);
				}
				else
				{
					system->mEntities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, SignatureID> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<SystEM>> mSystems{};
	};

}
