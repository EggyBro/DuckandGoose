/*!*************************************************************************
****
\file Logic.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Logic Component for all the scripts being used by each entity.
Contains a vector for scripts which is looped and calls each scripts update
function

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Logic.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "ExoEngine/Scripts/ButtonResponse.h"
#include "ExoEngine/Scripts/PlayerControl.h"
#include "ExoEngine/Scripts/EnemyScript.h"
#include "ExoEngine/Scripts/ScenerioScript.h"
#include "ExoEngine/Scripts/SliderScript.h"
#include "ExoEngine/Scripts/AudioManager.h"
#include "ExoEngine/Scripts/PauseMenu.h"
#include "ExoEngine/Scripts/HUDController.h"
#include "ExoEngine/Scripts/EnemyScript.h"
#include "ExoEngine/Scripts/GateController.h"
#include "ExoEngine/Scripts/BackgroundAudio.h"
#include "ExoEngine/Scripts/CutScene.h"
#include "ExoEngine/Scripts/HazardScript.h"
#include "ExoEngine/Scripts/DialogueManager.h"




namespace EM
{
	/*!*************************************************************************
	Ctor for Logic Component
	****************************************************************************/
	Logic::Logic() { entityID = GetComponentEntityID(); }

	/*!*************************************************************************
	Copy Ctor
	****************************************************************************/
	Logic::Logic(const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetScriptEntityID(this->GetComponentEntityID());
		}
	}
	/*!*************************************************************************
	Copy Assignment for operator overload
	****************************************************************************/
	Logic& Logic::operator= (const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetScriptEntityID(this->GetComponentEntityID());
		}
		return *this;
	}

	/*!*************************************************************************
	Sets the Script's entity to retrieve data only from that entity
	****************************************************************************/
	void Logic::SetScriptEntity(Entity entity)
	{
		this->SetComponentEntityID(entity);
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->SetScriptEntityID(this->GetComponentEntityID());
		}
	}

	/*!*************************************************************************
	Deserialize for Logic Component
	****************************************************************************/
	bool Logic::Deserialize(const rapidjson::Value& obj)
	{
		for (int i = 0; i < obj["ScriptCount"].GetInt(); ++i)
		{
			mScriptNameVector.push_back(obj[std::to_string(i).c_str()].GetString());
		}
		for (size_t j = 0; j < mScriptNameVector.size(); ++j)
		{
			if (mScriptNameVector[j] == "PlayerControl")
			{
				mScriptsVector.push_back(new PlayerControl(GetComponentEntityID()));
			}
			if (mScriptNameVector[j] == "EnemyScript")
			{
				mScriptsVector.push_back(new EnemyScript(GetComponentEntityID()));
			}
			if (mScriptNameVector[j] == "CollisionResponse")
			{
				mScriptsVector.push_back(new CollisionResponse());
			}
			if (mScriptNameVector[j] == "ButtonResponse")
			{
				mScriptsVector.push_back(new ButtonResponse());
			}
			if (mScriptNameVector[j] == "ScenerioScript")
			{
				mScriptsVector.push_back(new ScenerioScript());
			}
			if (mScriptNameVector[j] == "HUDController")
			{
				mScriptsVector.push_back(new HUDController());
			}
			if (mScriptNameVector[j] == "AudioManager")
			{
				mScriptsVector.push_back(new AudioManager());
			}
			if (mScriptNameVector[j] == "GateController")
			{
				mScriptsVector.push_back(new GateController(GetComponentEntityID()));
			}
			if (mScriptNameVector[j] == "BackgroundAudio")
			{
				mScriptsVector.push_back(new BackgroundAudio());
			}
			if (mScriptNameVector[j] == "SliderScript")
			{
				mScriptsVector.push_back(new SliderScript());
			}
			if (mScriptNameVector[j] == "PauseMenu")
			{
				mScriptsVector.push_back(new PauseMenu());
			}
			if (mScriptNameVector[j] == "HazardScript")
			{
				mScriptsVector.push_back(new HazardScript(GetComponentEntityID()));
			}
			if (mScriptNameVector[j] == "CutScene")
			{
				mScriptsVector.push_back(new CutScene());
			}
			if (mScriptNameVector[j] == "DialogueManager")
			{
				mScriptsVector.push_back(new DialogueManager());
			}
		}
		return true;
	}

	/*!*************************************************************************
	Serialize for Logic Component
	****************************************************************************/
	bool Logic::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		int i = 0;
		//writer->StartObject();
		//writer->StartArray();
		for (i = 0; i < mScriptNameVector.size(); ++i)
		{
			writer->Key(std::to_string(i).c_str());
			writer->String(mScriptNameVector[i].c_str());
		}
		//writer->EndArray();
		writer->Key("ScriptCount");
		writer->Int(i);
		//writer->EndObject();
		return true;
	}

	/*!*************************************************************************
	Inserts the scripts into the vector to loop through
	****************************************************************************/
	void Logic::InsertScript(IScript* script, Entity entity)
	{
		this->SetComponentEntityID(entity);
		script->SetScriptEntityID(this->GetComponentEntityID());
		mScriptNameVector.push_back(script->GetScriptName());
		mScriptsVector.push_back(script);
		//std::cout << "Script Vector: " << mScriptsVector.front()->GetScriptEntityID() << std::endl;
	}

	void Logic::DeleteScript(std::string scriptname)
	{
		for (int idx = 0;idx < mScriptNameVector.size(); idx++) {
			if (mScriptNameVector[idx] == scriptname) {
				mScriptNameVector.erase(mScriptNameVector.begin() + idx);
				mScriptsVector.erase(mScriptsVector.begin() + idx);
				//std::cout << "Deleted Script: " << scriptname << "\n";
			}
		}
	}

	/*!*************************************************************************
	Clear all Scripts inside the Vector
	****************************************************************************/
	void Logic::ClearAllScripts()
	{
		mScriptNameVector.clear();
		mScriptsVector.clear();
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->End();
		}
	}

	IScript* Logic::GetScriptByName(std::string ScriptName)
	{
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			if (mScriptNameVector[i] == ScriptName)
			{
				return mScriptsVector[i];
			}
		}
		std::cout << "'Script Not Found" << std::endl;
		return nullptr;
	}
}