#include "PlayerMovement.h"

namespace EM
{
	PlayerMovement::PlayerMovement() {}
	PlayerMovement* PlayerMovement::Clone() const
	{
		 return new PlayerMovement(*this); 
	}
	void PlayerMovement::Start() {}

	void PlayerMovement::Update(float Frametime)
	{
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetEntityID());
        vec2D vel = vec2D();
            if (p_Input->isKeyPressed(GLFW_KEY_UP)) {
                vel.y += 100.f;
            }
            if (p_Input->isKeyPressed(GLFW_KEY_RIGHT)) {
                vel.x += 100.f;
            }
            if (p_Input->isKeyPressed(GLFW_KEY_DOWN)) {
                vel.y -= 100.f;
            }
            if (p_Input->isKeyPressed(GLFW_KEY_LEFT)) {
                vel.x -= 100.f;
            }
        else {
            pRigid.SetVel(phys.friction(pRigid.GetVel(), Frametime));
        }
        pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, Frametime));

        //camera.SetPosition({pTrans.GetPos().x, pTrans.GetPos().y, 0.0f });
        vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
        pRigid.SetNextPos(nextPos);
	}
	void PlayerMovement::End()
	{

	}
}