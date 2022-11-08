#pragma once
#include "ExoEngine/Math/Physics.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
	class PhysicsSystem : public System
	{
	public:
		virtual std::string GetName() { return "Update Positions"; }
		virtual void Init() override;

		virtual void Update();

		void End();
	private:
    };
}