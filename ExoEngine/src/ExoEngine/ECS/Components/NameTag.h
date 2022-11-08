#pragma once
#include "IComponent.h"
#include "empch.h"

namespace EM
{
	class NameTag : public IComponent
	{
	public:
		NameTag();
		~NameTag() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void SetNameTag(std::string name) { mName = name; }
		std::string& GetNameTag() { return mName; }

	private:
		std::string mName;
	};
}