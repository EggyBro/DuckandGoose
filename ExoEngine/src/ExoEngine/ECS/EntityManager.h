/*!*************************************************************************
****
\file EntityManager.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains all the functions for distributing unique IDs to
all entities created, it does this using a container(queue) to store all
available entities allowed for the game

****************************************************************************
***/

#pragma once

#include "Types.h"
#include "ExoEngine/Log.h"

namespace EM
{
	class EntityManager
	{
	public:
		//Initializes the queue for for all available entity IDs
		EntityManager()
		{
			// Initialize the queue with all possible entity IDs up to the max number of entities
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				mAvailableEntities.push(entity);
			}
		}
		//Grabs a new id from the queue and return it
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
		//Destroy the entities id and push it to end of queue;
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

		Entity GetTotalEntities()
		{
			return mLivingEntityCount;
		}

		void SetTotalEntitiesForWorld(Entity entity)
		{
			while(mLivingEntityCount != entity)
			{
				CreateEntity();
			}
		}

		void ResetEntities()
		{
			std::fill(mSignatures.begin(), mSignatures.end(), 0);
			while (mLivingEntityCount != 0)
			{
				DestroyEntity(mLivingEntityCount);
			}
			mAvailableEntities = std::queue<Entity>();
			for (Entity entity = 1; entity < MAX_ENTITIES; ++entity)
			{
				mAvailableEntities.push(entity);
			}
		}

		
	private:

		// Queue of unused entity IDs
		std::queue<Entity> mAvailableEntities{};

		// Array of signatures where the index corresponds to the entity ID
		//std::array<SignatureID, MAX_ENTITIES> mSignatures{};
		std::array<Signature, MAX_ENTITIES> mSignatures{};

		// Total living entities - used to keep limits on how many exist
		Entity mLivingEntityCount{};
	};
}