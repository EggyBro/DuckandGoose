/*!*************************************************************************
****
\file SystemManager.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains a general implementation of a System Manager in
place of the ECS which is not integrated with the rest of the solution. 
It stores a vector of systems registered during runtime.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#pragma once
#include "ExoEngine/Core.h"
#include "Platform/System/System.h"

namespace EM {

	class SystemManager
	{
	public:

		/*!*************************************************************************
		Register System for use in ECS
		****************************************************************************/
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			return system;
		}

		/*!*************************************************************************
		Set System Signature for system to recognize what components to look out for
		****************************************************************************/
		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

			mSignatures.insert({ typeName, signature });
		}

		/*!*************************************************************************
		Remove Entity from system should entity be destroyed
		****************************************************************************/
		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;
				system->mEntities.erase(entity);
			}
		}
		/*!*************************************************************************
		Update Signature of Entity should component be removed from entity
		****************************************************************************/
		void EntitySignatureChanged(Entity entity, Signature entitySignature)
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
		// Unordered Map of Signatures 
		std::unordered_map<const char*, Signature> mSignatures{};
		// Unordered Map of Systems 
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
	};
}