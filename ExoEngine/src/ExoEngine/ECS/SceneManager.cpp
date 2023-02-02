/*!*************************************************************************
****
\file SceneManager.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  This file contains all the functions for loading and unloading the
level data into a JSON file. Currently on application end the ecs will be
saved into a json file for future loading

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "SceneManager.h"

namespace EM
{
	// Unique pointer to instance of Scene
	std::unique_ptr<SceneManager> SceneManager::m_instance;

	/*!*************************************************************************
	Returns an instance of the SceneManager
	****************************************************************************/
	std::unique_ptr<SceneManager>& SceneManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<SceneManager>();
		}
		return m_instance;
	}

	/*!*************************************************************************
	Initialize all registered components
	****************************************************************************/
	void SceneManager::Init()
	{
		p_ecs.RegisterComponent<Transform>();
		p_ecs.RegisterComponent<RigidBody>();
		p_ecs.RegisterComponent<Collider>();
		p_ecs.RegisterComponent<NameTag>();
		p_ecs.RegisterComponent<Sprite>();
		p_ecs.RegisterComponent<Logic>();
		p_ecs.RegisterComponent<Tag>();
		p_ecs.RegisterComponent<Audio>();
		p_ecs.RegisterComponent<HUDComponent>();
		p_ecs.RegisterComponent<Attributes>();
		//p_ecs.RegisterComponent<Button>();
		sceneToLoad = "";
	}

	//Due to restrictions of not using RTTR, components type cannot be deduced at runtime and hence needs to be checked manually
	//Will work on improving deserialization further
	/*!*************************************************************************
	Deserializes ECS entities and data from JSON file to build ECS (File loading)
	****************************************************************************/
	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		p_ecs.ResetEntities();
		p_ecs.SetTotalEntitiesForWorldBuild(obj["Number of Entities"]["Entities"].GetUint());
		for (ComponentType i = 0; i < p_ecs.GetTotalRegisteredComponents(); ++i)
		{
			p_ecs.ClearArrayForWorldBuild(i);
			auto aliveTotal = obj["Number of Entities"]["Entities"].GetUint();
			Entity aliveCount = 0;
			Entity j = 0;
			while(j < aliveTotal)
			{
				if (obj["EntityToIndexMap"][p_ecs.GetComponentTypeName(i).c_str()][j].GetUint() != 100)
				{
					Signature signature(obj["EntitySignatures"][j].GetString());
					if (signature.test(i))
					{
						//ADD COMPONENTS HERE FOR DESERIALIZE
						if (p_ecs.GetComponentTypeName(i) == "Transform")
						{
							Transform transform;
							if (transform.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Transform>(aliveCount == j ? aliveCount : j, transform);
							}
							std::cout << "Transform Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "RigidBody")
						{
							RigidBody rigidbody;
							if (rigidbody.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<RigidBody>(aliveCount == j ? aliveCount : j, rigidbody);
							}
							std::cout << "Rigid Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Collider")
						{
							Collider collider;
							if (collider.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Collider>(aliveCount == j ? aliveCount : j, collider);
							}
							std::cout << "Collider Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "NameTag")
						{
							NameTag nametag;
							if (nametag.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<NameTag>(aliveCount == j ? aliveCount : j, nametag);
							}
							std::cout << "NameTag Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Sprite")
						{
							Sprite sprite;
							if (sprite.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Sprite>(aliveCount == j ? aliveCount : j, sprite);
							}
							std::cout << "Sprite Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Logic")
						{
							Logic logic;
							if (logic.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Logic>(aliveCount == j ? aliveCount : j, logic);
							}
							std::cout << "Logic Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Tag")
						{
							Tag tag;
							if (tag.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Tag>(aliveCount == j ? aliveCount : j, tag);
							}
							std::cout << "Tag Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Audio")
						{
							Audio mAudio;
							if (mAudio.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Audio>(aliveCount == j ? aliveCount : j, mAudio);
							}
							std::cout << "Audio Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "HUDComponent")
						{
							HUDComponent mHUD;
							if (mHUD.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<HUDComponent>(aliveCount == j ? aliveCount : j, mHUD);
							}
							std::cout << "Hud Okay " << aliveCount << std::endl;
						}
						if (p_ecs.GetComponentTypeName(i) == "Attributes")
						{
							Attributes mAttributes;
							if (mAttributes.Deserialize(obj["Components"][p_ecs.GetComponentTypeName(i).c_str()][aliveCount].GetObj()))
							{
								p_ecs.AddComponent<Attributes>(aliveCount == j ? aliveCount : j, mAttributes);
							}
							std::cout << "Attributes Okay " << aliveCount << std::endl;
						}
					}
					++aliveCount;
				}
				++j;
			}
			/*for (Entity k = 0; k < MAX_ENTITIES; ++k)
			{
				p_ecs.GetEntityToIndexMapECS(i)[k] = obj["EntityToIndexMap"][p_ecs.GetComponentTypeName(i).c_str()][k].GetUint();
				p_ecs.GetIndexToEntityMapECS(i)[k] = obj["IndexToEntityMap"][p_ecs.GetComponentTypeName(i).c_str()][k].GetUint();
			}*/
		}
		return true;
	}


	//Due to restrictions of not using RTTR, components type cannot be deduced at runtime and hence needs to be checked manually
	//Will work on improving serialization further
	/*!*************************************************************************
	Serializes ECS entities and data to JSON file to save ECS (File saving)
	****************************************************************************/
	bool SceneManager::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Number of Entities");
		writer->StartObject();
		writer->Key("Entities");
		writer->Uint(p_ecs.GetTotalEntities());
		writer->EndObject();

		writer->Key("EntityToIndexMap");
		writer->StartObject();
		for (ComponentType i = 0; i < p_ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(p_ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			for (auto j = p_ecs.GetEntityToIndexMapECS(i).begin(); j != p_ecs.GetEntityToIndexMapECS(i).end(); ++j)
			{
				writer->Uint64(*j);
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->Key("IndexToEntityMap");
		writer->StartObject();
		for (ComponentType i = 0; i < p_ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(p_ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			for (auto j = p_ecs.GetIndexToEntityMapECS(i).begin(); j != p_ecs.GetIndexToEntityMapECS(i).end(); ++j)
			{
				writer->Uint(*j);
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->Key("EntitySignatures");
		writer->StartArray();
		auto aliveTotal = p_ecs.GetTotalEntities();
		Entity aliveCount = 0;
		Entity iterEntity = 0;
		while (aliveCount < aliveTotal)
		{
			writer->String(p_ecs.GetEntitySignature(iterEntity).to_string().c_str());
			if (p_ecs.GetEntitySignature(iterEntity).any())
			{
				aliveCount++;
			}
			iterEntity++;
		}
		writer->EndArray();

		writer->Key("Components");
		writer->StartObject();
		for (ComponentType i = 0; i < p_ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(p_ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			aliveTotal = p_ecs.GetTotalEntities();
			aliveCount = 0;
			Entity j = 0;
			while (aliveCount < aliveTotal)
			{
				if (p_ecs.GetEntitySignature(j).any())
				{
					aliveCount++;
				}
				if (p_ecs.GetEntitySignature(j).test(i))
				{
					//ADD COMPONENTS HERE FOR SERIALIZE
					if (p_ecs.GetComponentTypeName(i) == "Transform")
					{
						p_ecs.GetComponent<Transform>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "RigidBody")
					{
						p_ecs.GetComponent<RigidBody>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Collider")
					{
						p_ecs.GetComponent<Collider>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "NameTag")
					{
						p_ecs.GetComponent<NameTag>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Sprite")
					{
						p_ecs.GetComponent<Sprite>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Logic")
					{
						p_ecs.GetComponent<Logic>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Tag")
					{
						p_ecs.GetComponent<Tag>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Audio")
					{
						p_ecs.GetComponent<Audio>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "HUDComponent")
					{
						p_ecs.GetComponent<HUDComponent>(j).Serialize(writer);
					}
					if (p_ecs.GetComponentTypeName(i) == "Attributes")
					{
						p_ecs.GetComponent<Attributes>(j).Serialize(writer);
					}
				}
				j++;
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->EndObject();
		return true;
	}
}

void EM::SceneManager::setSceneToLoad(std::string s)
{
	sceneToLoad = s;
}

void EM::SceneManager::checkForSceneToLoad()
{
	if (sceneToLoad != "")
	{
		DeserializeFromFile(sceneToLoad);
		sceneToLoad = "";
	}
}

void EM::SceneManager::changeScene(std::string s)
{

}
