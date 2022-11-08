#include "NameTag.h"

namespace EM
{
	NameTag::NameTag() : mName{"none"} {}

	bool NameTag::Deserialize(const rapidjson::Value& obj)
	{
		mName = obj["NameTag"].GetString();
		return true;
	}

	bool NameTag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("NameTag");
		writer->String(mName.c_str());
		writer->EndObject();
		return true;
	}
}