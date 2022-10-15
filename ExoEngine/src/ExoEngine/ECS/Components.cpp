/*!*************************************************************************
****
\file Components.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains all the Various Components to be used in the ECS
in the future. Currently, Every Component is still handling its own data
by inheriting from an abstract class of the JSONSerializer to serialize and
deserialize its data

****************************************************************************
***/

#include "Components.h"

namespace EM
{
	//RigidBody
	RigidBody::RigidBody() : min{ vec2D() }, max{ vec2D() } 
	{
		//RigidBody::SerializeToFile("RigidBody.json");
	};
	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		min = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		max = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		vel = vec2D(obj["velX"].GetFloat(), obj["velY"].GetFloat());
		initvel = vec2D(obj["initX"].GetFloat(), obj["initY"].GetFloat());
		return true;
	}
	bool RigidBody::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("minX");
		writer->Double(min.value.x);
		writer->Key("minY");
		writer->Double(min.value.y);
		writer->Key("maxX");
		writer->Double(max.value.x);
		writer->Key("maxY");
		writer->Double(max.value.y);
		writer->Key("velX");
		writer->Double(vel.value.x);
		writer->Key("velY");
		writer->Double(vel.value.y);
		writer->Key("initX");
		writer->Double(initvel.value.x);
		writer->Key("initY");
		writer->Double(initvel.value.y);
		writer->EndObject();
		return true;
	}
	//End RigidBody

	//Transform
	Transform::Transform() : position{ vec2D() }, scale{ vec2D() } 
	{
		//Transform::SerializeToFile("Transform.json");
	};
	bool Transform::Deserialize(const rapidjson::Value& obj)
	{
		position = vec2D(obj["posX"].GetFloat(), obj["posY"].GetFloat());
		scale = vec2D(obj["scaleX"].GetFloat(), obj["scaleY"].GetFloat());
		rot = obj["Rot"].GetFloat();
		return true;
	}
	bool Transform::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("posX");
		writer->Double(position.value.x);
		writer->Key("posY");
		writer->Double(position.value.y);
		writer->Key("scaleX");
		writer->Double(scale.value.x);
		writer->Key("scaleY");
		writer->Double(scale.value.y);
		writer->Key("Rot");
		writer->Double(rot);
		writer->EndObject();
		return true;
	}
	//End Transform

	//Window
	WinData::WinData() : title{"Exomata"} , width {0}, height(0), currentWidth{0}, currentHeight{0}
	{
		//WinData::SerializeToFile("Window.json");
	};
	bool WinData::Deserialize(const rapidjson::Value& obj)
	{
		title = obj["Title"].GetString();
		width = obj["Width"].GetUint();
		height = obj["Height"].GetUint();
		currentWidth = obj["Cwidth"].GetUint();
		currentHeight = obj["Cheight"].GetUint();
		return true;
	}
	bool WinData::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Title");
		writer->String(title.c_str());
		writer->Key("Width");
		writer->Uint(width);
		writer->Key("Height");
		writer->Uint(height);
		writer->Key("Cwidth");
		writer->Uint(currentWidth);
		writer->Key("Cheight");
		writer->Uint(currentHeight);
		writer->EndObject();
		return true;
	}
}