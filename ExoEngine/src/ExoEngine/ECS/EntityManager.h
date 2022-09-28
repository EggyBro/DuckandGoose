#pragma once

#include "Types.h"
#include "ExoEngine/Log.h"

namespace EM
{
	class EM_API EntityManager
	{
	public:
		EntityManager()
		{
			// Initialize the queue with all possible entity IDs up to the max number of entities
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				mAvailableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
			//EM_EXO_ASSERT(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.")
			// Take an ID from the front of the queue
			Entity id = mAvailableEntities.front();
			mAvailableEntities.pop();	//Removes elements from the front of the queue
			++mLivingEntityCount;	//Dictates how many entities are alive

			return id;
		}

		void DestroyEntity(Entity entity)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");

			// Invalidate the destroyed entity's signature
			mSignatures[entity].reset();

			// Put the destroyed ID at the back of the queue
			mAvailableEntities.push(entity);
			--mLivingEntityCount;
		}

		//Parse the entity's signature into an array of Signatures
		void SetSignature(Entity entity, Signature signature)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");

			// Put this entity's signature into the array
			mSignatures[entity] = signature;
		}

		//Get the Signature of the entity
		Signature GetSignature(Entity entity)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");

			// Get this entity's signature from the array
			return mSignatures[entity];
		}

	private:

		// Queue of unused entity IDs
		std::queue<Entity> mAvailableEntities{};

		// Array of signatures where the index corresponds to the entity ID
		//std::array<SignatureID, MAX_ENTITIES> mSignatures{};
		std::vector<Signature> mSignatures {};

		// Total living entities - used to keep limits on how many exist
		uint32_t mLivingEntityCount{};
	};
}