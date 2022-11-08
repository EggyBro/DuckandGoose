#include "Logic.h"

namespace EM
{
	Logic::Logic() 
	{
	}

	Logic::Logic(const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetEntityID(this->entityID);
		}
	}

	Logic& Logic::operator= (const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetEntityID(this->entityID);
		}
		return *this;
	}

	void Logic::SetScriptEntity(Entity entity)
	{
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->SetEntityID(entity);
		}
	}

	bool Logic::Deserialize(const rapidjson::Value& obj)
	{
		mScriptNameVector.push_back(obj["ScriptName"].GetString());
		return true;
	}

	bool Logic::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ScriptName");
		writer->StartArray();
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			writer->String(mScriptNameVector[i].c_str());
		}
		writer->EndArray();
		writer->EndObject();
		return true;
	}

	void Logic::InsertScript(std::string name, IScript* script, Entity entity)
	{
		mScriptNameVector.push_back(name);
		mScriptsVector.push_back(script);
		entityID = entity;
	}
}