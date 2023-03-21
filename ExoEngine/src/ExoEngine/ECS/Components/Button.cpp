/*!*************************************************************************
****
\file Button.h
\author Lau Yong Hui
\par DP email: l.yonghui@gmail.com
\par Course: CSD2450 / GAM250
\par Section: a
\par Assignment GAM250
\date 2/11/2022
\brief  This file contains the class defination for Button component

Copyright (C) 2023 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#include "empch.h"
#include "Button.h"

EM::Button::Button()
{
}

bool EM::Button::Deserialize(const rapidjson::Value& obj)
{
	//mMin = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
	//mMax = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());

	selected = obj["selected"].GetBool();
	clicked = obj["clicked"].GetBool();
	return true;
}

bool EM::Button::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{	
		
	writer->StartObject();
	writer->Key("selected");
	writer->Bool(selected);
	writer->Key("clicked");
	writer->Bool(clicked);
	writer->EndObject();
	return true;
}
