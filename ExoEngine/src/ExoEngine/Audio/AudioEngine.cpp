/*!*************************************************************************
****
\file AudioEngine.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 10-10-2022
\brief  AudioEngine.cpp utilises FMOD Core to load, play, pause, stop and set
        volume
****************************************************************************
***/
#include "empch.h"

#include "AudioEngine.h"

std::unique_ptr< CAudioEngine> m_Instance;

std::unique_ptr<CAudioEngine>& CAudioEngine::GetInstance()
{
        if (!m_Instance)
        {
            m_Instance = std::make_unique<CAudioEngine>();
        }
        return m_Instance;
}

void CAudioEngine::ErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK) {
		//cout << "FMOD ERROR " << result << endl;
	}
}

FMOD::Sound* CAudioEngine::Loadsound(const std::string& strSoundName, bool b_Looping)
{
    auto tFoundIt = SoundMap.find(strSoundName); //find if sound is loaded
    FMOD::Sound* pSound = nullptr; //create sound
    if (tFoundIt != SoundMap.end())
        return pSound; //if loaded exit function

    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b_Looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

    CAudioEngine::ErrorCheck(mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
    if (pSound) 
    {
        SoundMap[strSoundName] = pSound; //if sound is created store in sound map
    }
    return pSound;
}

int CAudioEngine::PlaySound(const std::string& strSoundName,  float fVolumedB)
{
    int nChannelId = mnNextChannelId++;
    auto tFoundIt = SoundMap.find(strSoundName);
    FMOD::Sound* pSound;
    
    if (tFoundIt == SoundMap.end()) //iterate through channels, if not in any, load sound into a channel
    {
        pSound = Loadsound(strSoundName);
    }
    else
    {
        pSound = tFoundIt->second;
    }
    
    FMOD::Channel* pChannel = nullptr;

    ErrorCheck(mpSystem->playSound(pSound, nullptr, false, &pChannel));
    if (pChannel)
    {
        FMOD_MODE currMode;
        pSound->getMode(&currMode);
        CAudioEngine::ErrorCheck(pChannel->setVolume(VolumeTodB(fVolumedB)));
        ChannelMap[nChannelId] = pChannel;
    }
    return nChannelId;
}

void CAudioEngine::PauseSound(int channelID)
{
    auto it = ChannelMap.find(channelID);
    
    if (it != ChannelMap.end())
    {
        it->second->setPaused(true);
    }
}

void CAudioEngine::UnpauseSound(int channelID)
{
    auto it = ChannelMap.find(channelID);
    
    if (it != ChannelMap.end())
    {
        it->second->setPaused(false);
    }
}

void CAudioEngine::StopChannel(channel_groups chan)
{
    if (chan == channel_groups::master)
    {
        Master->stop();
    }

    else if (chan == channel_groups::bgm)
    {
        BGM->stop();
    }

    else if (chan == channel_groups::sfx)
    {
        SFX->stop();
    }
}


void CAudioEngine::SetVolume(int channelID, float vol)
{
    auto it = ChannelMap.find(channelID);
    
    if (it != ChannelMap.end())
    {
        it->second->setVolume(VolumeTodB(vol));
    }
}

void CAudioEngine::StopChannel(int channelID)
{
    auto it = ChannelMap.find(channelID); 
    
    if(it != ChannelMap.end())
    {
            it->second->stop();
    }   
}


float CAudioEngine::GetVolume(int channelID)
{
    float audio_volume = 0.0f;

    auto it = ChannelMap.find(channelID); 
    
    if(it != ChannelMap.end())
    {
       it->second->getVolume(&audio_volume);
    }
    return audio_volume;

}

//float CAudioEngine::ChangeVolume(int channelID, float)
//{
//    for (auto it = ChannelMap.find(channelID); it != ChannelMap.end(); it++)
//    {
//
//    }
//    return 0.0f;
//}

void CAudioEngine::Init()
{
	ErrorCheck(FMOD::System_Create(&mpSystem));

	mpSystem->init(1024, FMOD_INIT_NORMAL, NULL);
	mpSystem->createChannelGroup("Master", &Master);
	mpSystem->createChannelGroup("BGM", &BGM);
	mpSystem->createChannelGroup("SFX", &SFX);

	Master->addGroup(BGM);
	Master->addGroup(SFX);
}

void CAudioEngine::Update()
{
    std::vector<std::map<int, FMOD::Channel*>::iterator> pStoppedChannels;
    for (auto it = ChannelMap.begin(); it != ChannelMap.end(); ++it)
    {
        bool bIsPlaying = false;
        it->second->isPlaying(&bIsPlaying);
        

        if (!bIsPlaying)
        {
            pStoppedChannels.push_back(it);
        }
    }
    for (auto& it : pStoppedChannels)
    {
        ChannelMap.erase(it);
    }
    CAudioEngine::ErrorCheck(mpSystem->update());
}

void CAudioEngine::Release()
{
    //std::map<std::string, FMOD::Sound*>::iterator sound_it;
    // iterate through soundmap
    // release every sound
    for (auto sound_it = SoundMap.begin(); sound_it != SoundMap.end(); sound_it++)
    {
        sound_it->second->release();
    }
    
    // release every channel group
    // release systems
    Master->release();
    BGM->release();
    SFX->release();

    mpSystem->release();
}

float  CAudioEngine::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

float  CAudioEngine::VolumeTodB(float volume)
{
    float dec = 20.0f * log10f(volume);

    if (dec > 150.0f)
    {
        //error
        dec = 149.f;
    }

    return dec;
}

