#include "LogicSystem.h"
#include "ExoEngine/Timer/Time.h"

namespace EM
{
	void LogicSystem::Init()
	{
		/*auto mLogic = p_ecs.RegisterSystem<LogicSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Logic>());
			p_ecs.SetSystemSignature<LogicSystem>(signature);
		}*/
	}

	void LogicSystem::Update(float Frametime)
	{

		Timer::GetInstance().Start(Systems::LOGIC);
		Timer::GetInstance().GetDT(Systems::LOGIC);
		for (const auto& entity : mEntities)
		{
			auto& LogicComp = p_ecs.GetComponent<Logic>(entity);
			LogicComp.SetScriptEntity(entity);
			for (auto i = LogicComp.GetScript().begin(); i != LogicComp.GetScript().end(); ++i)
			{
				(*i)->Update(Frametime);
			}
		}
		Timer::GetInstance().Update(Systems::LOGIC);
	}

	void LogicSystem::End()
	{
		for (const auto& entity : mEntities)
		{
			auto& LogicComp = p_ecs.GetComponent<Logic>(entity);
			for (auto i = LogicComp.GetScript().begin(); i != LogicComp.GetScript().end(); ++i)
			{
				(*i)->End();
			}
		}
	}
		
}