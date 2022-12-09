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
****************************************************************************
***/
#include "empch.h"
#include "Sprite.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {

	/*!*************************************************************************
	Ctor for Sprite Component
	****************************************************************************/
	Sprite::Sprite() : m_texturename("Blank"), m_index({ 0.0f,0.0f }), mUVcooridnates({ 512.0f, 512.0f }),
		mIsSpriteSheet(false), mIsanimated(false), mDisplayTime(0.1667f){}

	/*!*************************************************************************
	Deserialize for Sprite Component
	****************************************************************************/
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{
		m_texturename = std::string(obj["TextureName"].GetString());
		m_index = vec2D(obj["Index_X"].GetFloat(), obj["Index_Y"].GetFloat());
		mUVcooridnates = vec2D(obj["Ucoordinates"].GetFloat(), obj["Vcoordinates"].GetFloat());
		mIsSpriteSheet = bool(obj["IsSpriteSheet"].GetBool());
		mIsanimated = bool(obj["IsAnimated"].GetBool());
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
		writer->String(m_texturename.c_str());
		writer->Key("Index_X");
		writer->Double(m_index.x);
		writer->Key("Index_Y");
		writer->Double(m_index.y);
		writer->Key("Ucoordinates");
		writer->Double(mUVcooridnates.x);
		writer->Key("Vcoordinates");
		writer->Double(mUVcooridnates.y);
		writer->Key("IsSpriteSheet");
		writer->Bool(mIsSpriteSheet);
		writer->Key("IsAnimated");
		writer->Bool(mIsanimated);
		writer->Key("DisplayTime");
		writer->Double(mDisplayTime);
		writer->EndObject();
		return true;
	}
	
	
}