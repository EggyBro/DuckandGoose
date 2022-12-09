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

#include "empch.h"
#include "Fmod/fmod/fmod.hpp"

#define p_Audio CAudioEngine::GetInstance()

 
class CAudioEngine //Handles loading, unloading, playing, stopping and changing sounds
{

        FMOD::System* mpSystem;

        int mnNextChannelId = 0;

        std::map<std::string, FMOD::Sound*> SoundMap;
        

        FMOD::ChannelGroup *BGM, *SFX, *Master;
        //FMOD::Channel*;
        FMOD::Sound* sound;

        //SoundMap mSounds;
        //ChannelMap mChannels;
    public:
        std::map<int, FMOD::Channel*> ChannelMap;

        enum class channel_groups { master, bgm, sfx };
        static std::unique_ptr<CAudioEngine>& GetInstance();

        void Init();
        void Update();
        void Release();
        void ErrorCheck(FMOD_RESULT result);

        //void LoadAudio(std::string filename);
        FMOD::Sound* Loadsound(const std::string& strSoundName, bool bLooping = false);
        //void UnLoadSound(const std::string& strSoundName);
        
        int PlaySound(const std::string& strSoundName, float fVolumedB = 0.0f);
        void PauseSound(int channelID);
        void UnpauseSound(int channelID);
        void StopChannel(channel_groups chan);
        void SetVolume(int channelID, float vol);
        void StopChannel(int channelID);
        float GetVolume(int channelID);
        bool IsPlaying(int nChannelId) const;
        float dbToVolume(float db);
        float VolumeTodB(float volume);
        int GetPlayingChannels() { return (int)ChannelMap.size(); }

};

#endif