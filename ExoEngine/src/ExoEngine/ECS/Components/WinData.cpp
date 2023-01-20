/*!*************************************************************************
****
\file WinData.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Window Component used to stored data regarding the window such as
height and width of the window

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "WinData.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for Window Data
	****************************************************************************/
	WinData::WinData() : mTitle{ "Exomata" }, mWidth{ 1920 }, mHeight{ 1080 }, mCurrentWidth{ 1920 }, mCurrentHeight{ 1080 } {}

	/*!*************************************************************************
	Deserialize for Window Data
	****************************************************************************/
	bool WinData::Deserialize(const rapidjson::Value& obj)
	{
		mTitle = obj["Title"].GetString();
		mWidth = obj["Width"].GetUint();
		mHeight = obj["Height"].GetUint();
		mCurrentWidth = obj["Cwidth"].GetUint();
		mCurrentHeight = obj["Cheight"].GetUint();
		return true;
	}
	/*!*************************************************************************
	Serialize for Window Data
	****************************************************************************/
	bool WinData::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Title");
		writer->String(mTitle.c_str());
		writer->Key("Width");
		writer->Uint(mWidth);
		writer->Key("Height");
		writer->Uint(mHeight);
		writer->Key("Cwidth");
		writer->Uint(mCurrentWidth);
		writer->Key("Cheight");
		writer->Uint(mCurrentHeight);
		writer->EndObject();
		return true;
	}
}