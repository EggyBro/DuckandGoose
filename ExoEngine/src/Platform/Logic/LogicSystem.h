#pragma once
#include "Platform/System/System.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ECS/ECS.h"

namespace EM
{
	class LogicSystem : public System
	{
	public:
		virtual std::string GetName() { return "LogicSystem"; }
		virtual void Init() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
	};
}