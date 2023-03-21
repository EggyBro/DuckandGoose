#include "empch.h"
#include "CollisionResponse.h"
#include "PlayerController.h"

#include "SkillsChest.h"

namespace EM
{
	SkillsChest::SkillsChest() : mState{}
	{
	}

	//SkillsChest::~SkillsChest()
	//{
	//}

	SkillsChest* SkillsChest::Clone() const
	{
		return new SkillsChest(*this);
	}

	void EM::SkillsChest::Start()
	{
	}

	void EM::SkillsChest::Update(float Frametime)
	{
		
	}

	void EM::SkillsChest::End()
	{
	}
	void SkillsChest::Animate(ChestState)
	{
	}
	void SkillsChest::SetState(ChestState state)
	{
		mState = state;
	}
	
	std::string SkillsChest::GetScriptName()
	{
		return "SkillsChest";
	}
}
