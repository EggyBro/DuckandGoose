/*!*************************************************************************
****
\file			Core.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			9-28-2022
\brief			This file contain the neccesary Macro that compile important 
				system to dll

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include <memory>

//Engine into dll
#ifdef EM_PLATFORM_WINDOWS
	#ifdef EM_BUILD_DLL
		#define EM_API __declspec(dllexport)
	#else
		#define EM_API __declspec(dllimport)
	#endif 
#else
	#error support Windows only!
#endif

#define BIT(x) (x << 1)
#define GETTEXTURE(x) ResourceManager::GetTexture(x)

namespace EM {

	template<typename T>
	using Singleton = std::unique_ptr<T>;
	template<typename T, typename ... Paras>
	constexpr Singleton<T> CreateSingleton(Paras&& ... paras)
	{
		return std::make_unique<T>(std::forward<Paras>(paras)...);
	}

	template<typename T>
	using MultiRefs = std::shared_ptr<T>;
	template<typename T, typename ... Paras>
	constexpr MultiRefs<T> CreateMultiRefs(Paras&& ... paras)
	{
		return std::make_shared<T>(std::forward<Paras>(paras)...);
	}
}