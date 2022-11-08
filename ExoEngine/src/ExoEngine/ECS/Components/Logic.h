#pragma once
#include "IComponent.h"
#include "ExoEngine/Scripts/IScript.h"

namespace EM
{
	class IScript;

	class Logic : public IComponent
	{
	public:
		Logic();
		Logic(const Logic& rhs);
		Logic& operator= (const Logic & rhs);
		~Logic() = default;

		std::vector<IScript*>& GetScript() { return mScriptsVector; }
		void SetScriptEntity(Entity entity);
		void InsertScript(std::string name, IScript* script, Entity entity);
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

	private:
		std::vector<std::string> mScriptNameVector;
		std::vector<IScript*> mScriptsVector;
	};
}