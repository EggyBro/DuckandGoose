#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyMovement : public IScript
	{
	public:
		EnemyMovement();
		~EnemyMovement() = default;
		virtual EnemyMovement* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
	private:
		entityPhysics mPhys;
	};
}