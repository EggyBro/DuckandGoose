/*!*************************************************************************
****
\file Attributes.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for attributes

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "empch.h"
#include "IComponent.h"

namespace EM
{
	class Attributes : public IComponent
	{
	public:

		enum class HazardTypes
		{
			HAZARD_EMPTY,
			HAZARD_GROUND,
			HAZARD_LASER
		};

		Attributes();
		~Attributes() = default;
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

		float mFiringCoolDown;
		float mFireDurationTimer;
		float mChargeCoolDown;
		int mHazardDmg;
		HazardTypes mHazardType;
	};
}