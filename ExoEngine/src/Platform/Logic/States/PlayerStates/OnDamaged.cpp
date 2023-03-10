#include "empch.h"
#include "Platform/Graphics/Camera2D.h"
#include "Platform/Graphics/Graphics.h"
#include "OnDamaged.h"
#include "OnIdle.h"
#include "OnDieded.h"

namespace EM
{
	float EaseInOutSine(float start, float end, float value)
	{
		end -= start;
		return -end * 0.5f * (cosf(M_PI * value) - 1) + start;
	}

	OnDamaged::OnDamaged(StateMachine* stateMachine) : mTimer{ 0.0f }, mDuration{ 0.2f }, mCamMinX{ EM::Graphic::camera.GetPosition().x }, mCamMaxX{ EM::Graphic::camera.GetPosition().x + 0.05f},
		mCamMinY{ EM::Graphic::camera.GetPosition().y }, mCamMaxY{ EM::Graphic::camera.GetPosition().y + 0.05f } {}

	IStates* OnDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnDamaged::OnEnter(StateMachine* stateMachine)
	{
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Enemy") {
				pDmg = p_ecs.GetComponent<EnemyAttributes>(i).mDamage;
			}
		}
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 0.5f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Damage");

		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 5))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[5].should_play = true;
		}
	}
	void OnDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		mTimer += Frametime;
		if (mTimer >= mDuration) {
			mTimer = 0.f;
			std::swap(mCamMinX, mCamMaxX);
			std::swap(mCamMinY, mCamMaxY);
		}
		EM::Graphic::camera.SetPosition({ EaseInOutSine(mCamMinX,mCamMaxX,mTimer/mDuration) , EaseInOutSine(mCamMinY,mCamMaxY,mTimer / mDuration), EM::Graphic::camera.GetPosition().z });

		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer -= Frametime;
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
		{
			stateMachine->ChangeState(new OnDieded(stateMachine));
		}
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}
	void OnDamaged::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}