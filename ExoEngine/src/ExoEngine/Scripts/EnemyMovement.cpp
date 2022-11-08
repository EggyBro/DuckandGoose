#include "EnemyMovement.h"

namespace EM
{
	EnemyMovement::EnemyMovement() {}
	EnemyMovement* EnemyMovement::Clone() const
	{
		return new EnemyMovement(*this);
	}
	void EnemyMovement::Start() {}

	void EnemyMovement::Update(float Frametime)
	{
		auto& transform = p_ecs.GetComponent<Transform>(GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetEntityID());
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Player>(i))
			{
				rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
			}
		}
		if (squarelength(rigidbody.GetDir()) < 3.0f)
		{
			rigidbody.SetVel(mPhys.accelent(rigidbody.GetDir(), rigidbody.GetVel(), Frametime));
			rigidbody.SetVel(mPhys.friction(rigidbody.GetVel(), Frametime));
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			rigidbody.SetNextPos(nextPos);
		}
	}

	void EnemyMovement::End() {}
}