/*!*************************************************************************
****
\file Audio.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-10-2022
\brief  This file is used to serialize and deserialize audio files

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "ExoEngine/ECS/Components/Audio.h"

/*!*************************************************************************
Constructor for audio component
****************************************************************************/
EM::Audio::Audio() : mAudioPath{ "" }, mChannelGroup{ AudioType::NONE }, is_Looping{ false } {}


/*!*************************************************************************
Deserialize audio component
****************************************************************************/
bool EM::Audio::Deserialize(const rapidjson::Value& obj)
{
	mAudioPath = std::string(obj["Audioname"].GetString());
	mChannelGroup = static_cast<AudioType>(obj["AudioType"].GetInt());
	is_Looping = obj["Looping"].GetInt();
	mVolume = obj["Volume"].GetFloat();

	return true;
}

/*!*************************************************************************
Serialise audio component
****************************************************************************/
bool EM::Audio::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();
	writer->Key("Audioname");
	writer->String(mAudioPath.c_str());
	writer->Key("AudioType");
	writer->Int(static_cast<int>(mChannelGroup));
	writer->Key("Looping");
	writer->Int(is_Looping);
	writer->EndObject();
	writer->Key("Volume");
	writer->Double(static_cast<double>(mVolume));

	return true;
}
