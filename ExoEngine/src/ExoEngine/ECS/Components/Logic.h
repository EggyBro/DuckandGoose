/*!*************************************************************************
****
\file Logic.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Logic Component for all the scripts being used by each entity.
Contains a vector for scripts which is looped and calls each scripts update
function

****************************************************************************
***/

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
		Logic& operator= (const Logic& rhs);
		~Logic() = default;

		std::vector<IScript*>& GetScript() { return mScriptsVector; }
		void SetScriptEntity(Entity entity);
		void InsertScript(IScript* script, Entity entity);
		void ClearAllScripts();
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	private:
		std::vector<std::string> mScriptNameVector;
		std::vector<IScript*> mScriptsVector;
	};
}