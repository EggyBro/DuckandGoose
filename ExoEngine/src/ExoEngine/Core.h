/*!*************************************************************************
****
\file			Core.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the neccesary Macro that compile important 
				system to dll


****************************************************************************
***/
#pragma once
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