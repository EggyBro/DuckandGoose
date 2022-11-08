#pragma once
#include "IComponent.h"

namespace EM
{
	class Player : public IComponent
	{
	public:
		Player();
		~Player() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
	private:
		int mHealth;
	};
}