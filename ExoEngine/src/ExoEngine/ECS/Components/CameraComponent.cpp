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
#include "empch.h"
#include "CameraComponent.h"

namespace EM {

	/*!*************************************************************************
	Constructor for camera component
	****************************************************************************/
	CameraComponent::CameraComponent()
	{
	}

	/*!*************************************************************************
	Derserialize camera component
	****************************************************************************/
	bool CameraComponent::Deserialize(const rapidjson::Value& obj)
	{
		UNREFERENCED_PARAMETER(obj);
		return false;
	}

	/*!*************************************************************************
	Serialize camera component
	****************************************************************************/
	bool CameraComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		UNREFERENCED_PARAMETER(writer);
		return false;
	}
}