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
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {

	/*!*************************************************************************
	Ctor for Sprite Component
	****************************************************************************/
	Sprite::Sprite() : mTextureName("Blank"), mIndex({ 0.0f,0.0f }), mUVcooridnates({ 512.0f, 512.0f }),
		is_SpriteSheet(false), is_Animated(false), mDisplayTime(0.1667f){}

	/*!*************************************************************************
	Deserialize for Sprite Component
	****************************************************************************/
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{
		mTextureName = std::string(obj["TextureName"].GetString());
		mIndex = vec2D(obj["Index_X"].GetFloat(), obj["Index_Y"].GetFloat());
		mUVcooridnates = vec2D(obj["Ucoordinates"].GetFloat(), obj["Vcoordinates"].GetFloat());
		is_SpriteSheet = bool(obj["IsSpriteSheet"].GetBool());
		is_Animated = bool(obj["IsAnimated"].GetBool());
		mDisplayTime = float(obj["DisplayTime"].GetFloat());
		return true;
	}

	/*!*************************************************************************
	Serialize for Sprite Component
	****************************************************************************/
	bool Sprite::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("TextureName");
		writer->String(mTextureName.c_str());
		writer->Key("Index_X");
		writer->Double(mIndex.x);
		writer->Key("Index_Y");
		writer->Double(mIndex.y);
		writer->Key("Ucoordinates");
		writer->Double(mUVcooridnates.x);
		writer->Key("Vcoordinates");
		writer->Double(mUVcooridnates.y);
		writer->Key("IsSpriteSheet");
		writer->Bool(is_SpriteSheet);
		writer->Key("IsAnimated");
		writer->Bool(is_Animated);
		writer->Key("DisplayTime");
		writer->Double(mDisplayTime);
		writer->EndObject();
		return true;
	}
	
	
}