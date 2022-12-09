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