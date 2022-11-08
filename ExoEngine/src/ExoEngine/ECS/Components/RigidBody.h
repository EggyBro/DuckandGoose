#pragma once
#include "ExoEngine/Math/Vmath.h"
#include "IComponent.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM
{
	//RigidBody Component
	//Velocity
	//Direction
	//Friction
	//Restitution

	class RigidBody : public IComponent
	{
	public:
		RigidBody();
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		vec2D& GetVel() { return mVelocity; }
		vec2D& GetDir() { return mDirection; }
		vec2D& GetNextPos() { return NextPos; }
		float& GetFriction() { return mFriction; }
		float& GetRestitution() { return mRestitution; }

		void SetVel(vec2D vel) { mVelocity = vel; }
		void SetDir(vec2D dir) { mDirection = dir; }
		void SetNextPos(vec2D vec) { NextPos = vec; }
		void SetVel(float velX, float velY) { mVelocity = vec2D(velX, velY); }
		void SetDir(float dirX, float dirY) { mDirection = vec2D(dirX, dirY); }
		void SetFriction(float value) { mFriction = value; }
		void SetRestitution(float value) { mRestitution = value; }
    
	private:
		vec2D mVelocity;
		vec2D mDirection;
		vec2D NextPos;
		float mFriction;
		float mRestitution;
	};

}