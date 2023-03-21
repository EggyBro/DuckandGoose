#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class SkillsChest : public IScript
	{
	public:
		enum class ChestState
		{
			Alive,
			Dead
		};

	SkillsChest();
	~SkillsChest() = default;
	virtual SkillsChest* Clone() const override;
	virtual void Start() override;
	virtual void Update(float Frametime) override;
	virtual void End() override;
	virtual std::string GetScriptName() override;

	void Animate(ChestState);
	void SetState(ChestState state);
	
	ChestState& GetState()
	{
		return mState;
	}

	private:
		ChestState mState;
	};
}