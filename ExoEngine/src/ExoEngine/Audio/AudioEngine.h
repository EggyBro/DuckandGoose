/*!*************************************************************************
****
\file AudioEngine.h
\author Cheung Jun Yin Matthew, Tan Ek Hern
\par DP email: j.cheung@digipen.edu, t.ekhern@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 10-10-2022
\brief  Header file for AudioEngine.cpp

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "empch.h"
#include "Fmod/fmod/fmod.hpp"
#include "ExoEngine/ECS/Components/Audio.h"

#define p_Audio CAudioEngine::GetInstance()


class CAudioEngine //Handles loading, unloading, playing, stopping and changing sounds
{

    FMOD::System* mpSystem;

    int mNextChannelId = 1;

    std::map<std::string, FMOD::Sound*> mSoundMap;


    FMOD::ChannelGroup* BGM, * SFX, * Master;
    //FMOD::Channel*;
    FMOD::Sound* Msound;

    //SoundMap mSounds;
    //ChannelMap mChannels;
public:
    std::map<int, FMOD::Channel*> mChannelMap;

    enum class channel_groups { master, bgm, sfx };
    static std::unique_ptr<CAudioEngine>& GetInstance();

    void Init();
    void Update();
    void Release();
    void ErrorCheck(FMOD_RESULT result);

    //void LoadAudio(std::string filename);
    FMOD::Sound* Loadsound(const std::string& strSoundName, bool bLooping = false);
    //void UnLoadSound(const std::string& strSoundName);

    int PlaySound(const std::string& strSoundName, EM::Audio::AudioType chgrp);
    void PauseSound(int channelID);
    void UnpauseSound(int channelID);
    void StopChannel(channel_groups chan);
    void SetVolume(int channelID, float vol);
    void StopChannel(int channelID);
    float GetVolume(int channelID);
    void SetLooping(const std::string& strSoundName, bool in);
    bool IsPlaying(int nChannelId) const;
    float dbToVolume(float db);
    float VolumeTodB(float volume);
    int GetPlayingChannels() { return (int)mChannelMap.size(); }
    void SetVolumeByChannel(FMOD::ChannelGroup* ch, float volume) { ch->setVolume(volume); }
    float GetVolumeByChannel(FMOD::ChannelGroup* ch);
    FMOD::ChannelGroup* GetMasterChannelGroup() { return Master; }
    FMOD::ChannelGroup* GetBGMChannelGroup() { return BGM; }
    FMOD::ChannelGroup* GetSFXChannelGroup() { return SFX; }
};

#endif