#pragma once

#include "empch.h"
#include "Serialization/JSONserialization.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM
{

	struct Transform : public JSONSerializer
	{
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

		const float& Scale() const { return _scale; }
		void Scale(const float& scale) { _scale = scale; }

		const float& Rotation() const { return _rotation; }
		void Rotation(const float& rotation) { _rotation = rotation; }

		const float& Position() const { return _position; }
		void Position(const float& position) { _position = position; }

		float _scale, _rotation, _position;
	};

	class Player : public JSONSerializer
	{
	public:
		Player();
		~Player() = default;

		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

		// Getters/Setters.
		const vec2D& Position() const { return _Position; }
		void Position(const vec2D& position) { _Position = position; }

		const vec2D& Velocity() const { return _Velocity; }
		void Velocity(const vec2D& position) { _Velocity = position; }

	private:
		vec2D _Position;
		vec2D _Velocity;
		Transform _transform;
	};
}