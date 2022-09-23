#pragma once

#include "Types.h"
#include "empch.h"

namespace EM
{
	class EM_API SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Registering systEM more than once.");

			auto systEM = std::make_shared<T>();
			mSystems.insert({ typeName, systEM });
			return systEM;
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
				auto const& systEM = pair.second;


				systEM->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(EntityID entity, SignatureID entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& systEM = pair.second;
				auto const& systEMSignature = mSignatures[type];

				if ((entitySignature & systEMSignature) == systEMSignature)
				{
					systEM->mEntities.insert(entity);
				}
				else
				{
					systEM->mEntities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, SignatureID> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<SystEM>> mSystems{};
	};

}
