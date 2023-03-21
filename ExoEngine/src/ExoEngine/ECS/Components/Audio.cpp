/*!*************************************************************************
****
\file Audio.cpp
\author Cheung Jun Yin Matthew, Tan Ek Hern
\par DP email: j.cheung@digipen.edu, t.ekhern@digipen.edu
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
EM::Audio::Audio() : AudioArr(), bgmVol{ 1.0f }, sfxVol{ 1.0f }, masterVol{ 1.0f } {}


/*!*************************************************************************
Deserialize audio component
****************************************************************************/
bool EM::Audio::Deserialize(const rapidjson::Value& obj)
{
	for (int i = 0; i < obj["AudioArrCount"].GetInt(); ++i)
	{
		AudioPiece na{};
		na.mAudioPath = obj[std::to_string(i).c_str()].GetObj()["AudioPath"].GetString();
		na.mChannelGroup = static_cast<AudioType>(obj[std::to_string(i).c_str()].GetObj()["Channel"].GetInt());
		na.is_Looping = obj[std::to_string(i).c_str()].GetObj()["IsLooping"].GetBool();
		na.mChannel = 0;
		na.should_play = false;
		na.should_stop = false;
		na.is_Playing = false;
		na.triggered = false;
		AudioArr.emplace_back(na);
	}
	bgmVol = (float)obj["BGM Volume"].GetDouble();
	sfxVol = (float)obj["SFX Volume"].GetDouble();
	masterVol = (float)obj["Master Volume"].GetDouble();
	return true;
}

/*!*************************************************************************
Serialise audio component
****************************************************************************/
bool EM::Audio::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{
	int i = 0;
	//writer->StartObject();
	for (i = 0; i < AudioArr.size(); ++i)
	{
		writer->Key(std::to_string(i).c_str());
		writer->StartObject();
		writer->Key("AudioPath");
		writer->String(AudioArr[i].mAudioPath.c_str());
		writer->Key("Channel");
		writer->Int(static_cast<int>(AudioArr[i].mChannelGroup));
		writer->Key("IsLooping");
		writer->Bool(AudioArr[i].is_Looping);
		writer->EndObject();
	}
	writer->Key("AudioArrCount");
	writer->Int(i);
	writer->Key("BGM Volume");
	writer->Double(bgmVol);
	writer->Key("SFX Volume");
	writer->Double(sfxVol);
	writer->Key("Master Volume");
	writer->Double(masterVol);
	//writer->EndObject();
	return true;
}
