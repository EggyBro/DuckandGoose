/*!*************************************************************************
****
\file HUDComponent.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief This file contains class and functions used by the HUD component


Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"
namespace EM {

	class HUDComponent : public IComponent
	{
	public:
		enum class ElementType
		{
			Static,
			HealthBar,
			BlockBar,
			DashBar,
			ChargeAtk,
			Text
		};
		HUDComponent();
		~HUDComponent() = default;
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
		ElementType GetType() { return mType; }
		vec2D& GetOffset() { return offset; }
		void SetType(ElementType in) { mType = in; }
		void SetOffset(vec2D in) { offset = in; }
		std::string GetAtk() { return atk; }
		void SetAtk(std::string in) { atk = in; }
		std::string GetDef() { return def; }
		void SetDef(std::string in) { def = in; }
		std::string GetSpd() { return spd; }
		void SetSpd(std::string in) { spd = in; }
		std::string GetCombo() { return combo; }
		void SetCombo(std::string in) { combo = in; }
	private:
		ElementType mType;
		vec2D offset;
		std::string atk;
		std::string def;
		std::string spd;
		std::string combo;
	};
}
