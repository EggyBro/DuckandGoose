#include "empch.h"
#include "PhysicsSystem.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	//extern ECS ecs;

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Update()
	{
		for (auto& Entity : mEntities)
		{
			auto& mTrans = p_ecs.GetComponent<Transform>(Entity);
			auto& mRigid = p_ecs.GetComponent<RigidBody>(Entity);
			mTrans.SetPos(mRigid.GetNextPos());
		}
	}

	void PhysicsSystem::End() {

	}
}