#include "empch.h"
#include "Attributes.h"

namespace EM
{
	Attributes::Attributes() : mHealth(100), mDamage(50) {};

	bool Attributes::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		mDamage = obj["Damage"].GetInt();
		return true;
	}

	bool Attributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->Key("Damage");
		writer->Int(mDamage);
		writer->EndObject();
		return true;
	}
}