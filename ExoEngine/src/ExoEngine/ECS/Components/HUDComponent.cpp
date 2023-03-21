/*!*************************************************************************
****
\file HUDComponent.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief This file contains class and function definitions used by the HUD component

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "HUDComponent.h"

namespace EM {

	/*!*************************************************************************
	Constructor for HUD component
	****************************************************************************/
	HUDComponent::HUDComponent() : mType{ ElementType::Static }, offset{ vec2D() } {}

	/*!*************************************************************************
	Derserialize HUD component
	****************************************************************************/
	bool HUDComponent::Deserialize(const rapidjson::Value& obj)
	{
		mType = static_cast<ElementType>(obj["ElementType"].GetInt());
		offset = vec2D(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat());
		return true;
	}

	/*!*************************************************************************
	Serialize HUD component
	****************************************************************************/
	bool HUDComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("ElementType");
		writer->Int(static_cast<int>(mType));
		writer->Key("offsetX");
		writer->Double(offset.x);
		writer->Key("offsetY");
		writer->Double(offset.y);
		//writer->EndObject();
		return true;
	}
}