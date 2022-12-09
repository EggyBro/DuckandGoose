/*!*************************************************************************
****
\file IScript.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Abstract class for IScript

****************************************************************************
***/

#pragma once
#include "ExoEngine/ECS/Types.h"
#include "ExoEngine/ECS/ECS.h"

namespace EM
{
	/*!*************************************************************************
	Interface for Script
	****************************************************************************/
	class IScript
	{
	public:
		virtual ~IScript() = default;
		virtual void Start() {};
		virtual void Update(float Frametime) { UNREFERENCED_PARAMETER(Frametime); };
		virtual void End() {};
		virtual IScript* Clone() const = 0;
		virtual std::string GetScriptName() = 0;

		void SetScriptEntityID(Entity& entity) { entityID = entity; }
		Entity& GetScriptEntityID() { return entityID; }
	private:
		Entity entityID;
	};
}