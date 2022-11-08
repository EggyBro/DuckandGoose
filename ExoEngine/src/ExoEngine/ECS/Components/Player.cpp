#include "Player.h"

namespace EM
{
	Player::Player() : mHealth{ 100 } {}

	bool Player::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		return true;
	}
	bool Player::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->EndObject();
		return true;
	}
}