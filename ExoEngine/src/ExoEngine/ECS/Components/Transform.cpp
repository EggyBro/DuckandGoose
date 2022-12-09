/*!*************************************************************************
****
\file Transform.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Transform component used to set the pos, scale and rot of the
entity and used for various systems such as graphics to render images

****************************************************************************
***/
#include "empch.h"
#include "Transform.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for Transform Component
	****************************************************************************/
	Transform::Transform() : mPosition{ vec2D(0.0f,0.0f) }, mScale{ vec2D(1.0f,1.0f) }, mRot{ 0.0f } {}

	/*!*************************************************************************
	Deserialize for Transform Component
	****************************************************************************/
	bool Transform::Deserialize(const rapidjson::Value& obj)
	{
		mPosition = vec2D(obj["posX"].GetFloat(), obj["posY"].GetFloat());
		mScale = vec2D(obj["scaleX"].GetFloat(), obj["scaleY"].GetFloat());
		mRot = obj["Rot"].GetFloat();
		return true;
	}

	/*!*************************************************************************
	Serialize for Transform Component
	****************************************************************************/
	bool Transform::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("posX");
		writer->Double(mPosition.x);
		writer->Key("posY");
		writer->Double(mPosition.y);
		writer->Key("scaleX");
		writer->Double(mScale.x);
		writer->Key("scaleY");
		writer->Double(mScale.y);
		writer->Key("Rot");
		writer->Double(mRot);
		writer->EndObject();
		return true;
	}
	//End Transform
}