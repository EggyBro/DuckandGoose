/*!*************************************************************************
****
\file Button.h
\author Lau Yong Hui
\par DP email: l.yonghui@gmail.com
\par Course: CSD2450 / GAM250
\par Section: a
\par Assignment GAM250
\date 2/11/2022
\brief  This file contains the class defination for Button component

Copyright (C) 2023 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#pragma once
#include "ExoEngine/Math/Vmath.h"
#include "IComponent.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM
{
	//RigidBody Component
	//Velocity
	//Direction
	//Friction
	//Restitution

	class Button : public IComponent
	{
	public:
		Button();
		~Button() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		bool& CheckIfselected() { return selected; }
		bool& CheckIfclicked() { return clicked; }

		void ToggleSelect() { selected = selected ? false : true; }//if highlighted play animation
		void Toggleclicked() { clicked = clicked ? false : true; }
		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	private:
		
		bool selected;
		bool clicked;
	};

}