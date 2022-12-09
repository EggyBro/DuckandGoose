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
****************************************************************************
***/
#include "empch.h"
#include "ExoEngine/ECS/Components/Audio.h"

/*!*************************************************************************
Constructor for audio component
****************************************************************************/
EM::Audio::Audio() : mAudiopath{ "" }, channelgroup{ AudioType::NONE }, is_looping{ false } {}


/*!*************************************************************************
Deserialize audio component
****************************************************************************/
bool EM::Audio::Deserialize(const rapidjson::Value& obj)
{
	mAudiopath = std::string(obj["Audioname"].GetString());
	channelgroup = static_cast<AudioType>(obj["AudioType"].GetInt());
	is_looping = obj["Looping"].GetInt();
	volume = obj["Volume"].GetFloat();

	return true;
}

/*!*************************************************************************
Serialise audio component
****************************************************************************/
bool EM::Audio::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();
	writer->Key("Audioname");
	writer->String(mAudiopath.c_str());
	writer->Key("AudioType");
	writer->Int(static_cast<int>(channelgroup));
	writer->Key("Looping");
	writer->Int(is_looping);
	writer->EndObject();
	writer->Key("Volume");
	writer->Double(static_cast<double>(volume));

	return true;
}
