/*!*************************************************************************
****
\file Audio.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-10-2022
\brief Header file for Audio.cpp
****************************************************************************
***/
#pragma once
#include "IComponent.h"

namespace EM
{

	class Audio : public IComponent
	{
	public:
		enum class AudioType
		{
			NONE,
			MASTER,
			BGM,
			SFX
		};
		Audio();
		~Audio() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
		
		void SetAudioPath(std::string input) { mAudiopath = input; }
		void SetChannelGroup(AudioType input) { channelgroup = input; }
		void SetLooping(bool isplayed) { is_looping = isplayed; }
		void SetVolume(float vol) { volume = vol; }

		std::string GetAudioPath() { return mAudiopath; }
		AudioType GetChannelGroup() { return channelgroup; }
		bool GetLooping() { return is_looping; }
		float GetVolume() { return volume; }

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

		//Audio component
		//	Singular piece of audio that can be set to play upon a specific event.
		//	Toggle looping.
		

	private:
		std::string mAudiopath; 
		AudioType channelgroup;
		bool is_looping;
		float volume;

	};
}