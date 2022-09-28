#include "Object.h"

namespace EM
{
	bool Transform::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("Position");
		writer->Double(_position);

		writer->String("Rotation");
		writer->Double(_rotation);

		writer->String("Scale");
		writer->Double(_scale);

		writer->EndObject();

		return true;
	}

	bool Transform::Deserialize(const rapidjson::Value& obj)
	{
		Position(obj["Position"].GetDouble());
		Rotation(obj["Rotation"].GetDouble());
		Scale(obj["Scale"].GetDouble());
		
		return true;
	}

	Player::Player() : _Position(vec2D()), _Velocity(vec2D()) {};

	bool Player::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("PositionX");
		writer->Double(_Position.value.x);
		writer->String("PositionY");
		writer->Double(_Position.value.y);

		writer->String("VelocityX");
		writer->Double(_Velocity.value.x);
		writer->String("VelocityY");
		writer->Double(_Velocity.value.y);

		writer->EndObject();

		return true;
	}

	bool Player::Deserialize(const rapidjson::Value& obj)
	{
		vec2D position = vec2D(obj["PositionX"].GetDouble(), obj["PositionY"].GetDouble());
		Position(position);
		vec2D velocity = vec2D(obj["VelocityX"].GetDouble(), obj["VelocityY"].GetDouble());
		Velocity(velocity);
		return true;
	}
}