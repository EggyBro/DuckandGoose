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

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
		
		void SetAudioPath(std::string input) { mAudioPath = input; }
		void SetChannelGroup(AudioType input) { mChannelGroup = input; }
		void SetLooping(bool isplayed) { is_Looping = isplayed; }
		void SetVolume(float vol) {mVolume = vol; }

		std::string GetAudioPath() { return mAudioPath; }
		AudioType GetChannelGroup() { return mChannelGroup; }
		bool GetLooping() { return is_Looping; }
		float GetVolume() { return mVolume; }

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
		std::string mAudioPath{};
		AudioType mChannelGroup{};
		bool is_Looping{};
		float mVolume{};

	};
}