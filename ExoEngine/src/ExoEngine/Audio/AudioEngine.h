/*!*************************************************************************
****
\file AudioEngine.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 10-10-2022
\brief  Header file for AudioEngine.cpp  
****************************************************************************
***/
#pragma once

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "Fmod/fmod/fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

#define p_Audio CAudioEngine::GetInstance()

 
class CAudioEngine //Handles loading, unloading, playing, stopping and changing sounds
{

        FMOD::System* mpSystem;

        int mnNextChannelId;

        std::map<std::string, FMOD::Sound*> SoundMap;
        std::map<int, FMOD::Channel*> ChannelMap;

        FMOD::ChannelGroup *BGM, *SFX, *Master;
        //FMOD::Channel*;
        FMOD::Sound* sound;

        //SoundMap mSounds;
        //ChannelMap mChannels;
    public:
        enum class channel_groups { master, bgm, sfx };
        static std::unique_ptr<CAudioEngine>& GetInstance();

        void Init();
        void Update();
        void Release();
        void ErrorCheck(FMOD_RESULT result);

        FMOD::Sound* Loadsound(const std::string& strSoundName, bool bLooping = false);
        //void UnLoadSound(const std::string& strSoundName);
        
        int PlaySound(const std::string& strSoundName, float fVolumedB = 0.0f);
        void PauseSound(int channelID);
        void UnpauseSound(int channelID);
        void StopChannel(channel_groups chan);
        void SetVolume(int channelID, float vol);
        //void PlayEvent(const std::string& strEventName);
        //void SetVolume(float vol);
        void StopChannel(int channelID);
        float GetVolume(int channelID);
        float ChangeVolume(int channelID, float vol);
        /* 
        change vol(int channelID, float)
        */

        //void StopEvent(const std::string& strEventName, bool bImmediate = false);

        //void StopAllChannels();

        void SetChannelvolume(int nChannelId, float fVolumedB);
        bool IsPlaying(int nChannelId) const;
        //bool IsEventPlaying(const std::string& strEventName) const;
        float dbToVolume(float db);
        float VolumeTodB(float volume);
        //FMOD_VECTOR VectorToFmod(const Vector3& vPosition);

};

#endif