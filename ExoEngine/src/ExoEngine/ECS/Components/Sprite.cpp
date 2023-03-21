/*!*************************************************************************
****
\file			Sprite.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-2-2022
\brief			This file contain the defintion for Sprite class
				which set private variables with default value and de/serialize
				the necessary component variables

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Sprite.h"
//#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/Animation/Animation.h"
namespace EM {

	/*!*************************************************************************
	Ctor for Sprite Component
	****************************************************************************/
	Sprite::Sprite() : mTextureName("Blank"), Index({ 0,0 }), mUVcooridnates({ 512.0f, 512.0f }),
		is_SpriteSheet(false), is_Animated(false), mAlpha(1), MaxIndex_X(0),displayTime(GetMaxIndex()), internaltimer(0){}

	/*!*************************************************************************
	Deserialize for Sprite Component
	****************************************************************************/
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{
		mTextureName = std::string(obj["TextureName"].GetString());
		Index.x = int(obj["Index_X"].GetInt());
		Index.y = int(obj["Index_Y"].GetInt());
		mUVcooridnates = vec2D(obj["Ucoordinates"].GetFloat(), obj["Vcoordinates"].GetFloat());
		is_SpriteSheet = bool(obj["IsSpriteSheet"].GetBool());
		is_Animated = bool(obj["IsAnimated"].GetBool());
		MaxIndex_X = int(obj["MaxIndex"].GetInt());
		for (auto i = 0; i < MaxIndex_X; i++)
		{
			std::string DpNum;
			DpNum = "DisplayTime " + std::to_string(i);
			float individualtime = float(obj[DpNum.c_str()].GetFloat());
			displayTime.push_back(individualtime);
		}
		if (is_Animated)
		{
			Animation::spriteContainer.emplace(mTextureName, displayTime);
		}
			
		return true;
	}

	/*!*************************************************************************
	Serialize for Sprite Component
	****************************************************************************/
	bool Sprite::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("TextureName");
		writer->String(mTextureName.c_str());
		writer->Key("Index_X");
		writer->Int(Index.x);
		writer->Key("Index_Y");
		writer->Int(Index.y);
		writer->Key("Ucoordinates");
		writer->Double(mUVcooridnates.x);
		writer->Key("Vcoordinates");
		writer->Double(mUVcooridnates.y);
		writer->Key("IsSpriteSheet");
		writer->Bool(is_SpriteSheet);
		writer->Key("IsAnimated");
		writer->Bool(is_Animated);
		writer->Key("MaxIndex");
		writer->Int(MaxIndex_X);
		for (auto i = 0; i < displayTime.size(); i++)
		{
			std::string DpNum;
			DpNum = "DisplayTime " + std::to_string(i);
			writer->Key(DpNum.c_str());
			writer->Double(displayTime[i]);
		}
		//writer->EndObject();
		return true;
	}
	
	
}