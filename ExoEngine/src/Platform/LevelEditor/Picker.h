/*!*************************************************************************
****
\file			Picker.h
\author			Huang Xin Xiang
\par DP email:  h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-28-2022
\brief			Picker.h is the header file for picker.cpp

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "Platform/Graphics/Camera2D.h"
namespace EM {

	struct AABB
	{
		glm::vec2 min;
		glm::vec2 max;
	};

	struct Picker
	{
		static int Pick(Camera2D* camera, std::multimap<float, Transform*> scene);
	};
}