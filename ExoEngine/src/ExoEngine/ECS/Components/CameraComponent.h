/*!*************************************************************************
****
\file			CameraComponent.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-18-2022
\brief			This file contains the class definitions for camera component

****************************************************************************
***/
#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"

namespace EM {

	class CameraComponent : public IComponent
	{
	public:
		CameraComponent();
		~CameraComponent() = default;
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
	};
}
