/*!*************************************************************************
****
\file			Application.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the neccesary declaration functions for class Application.

****************************************************************************
***/
#pragma once

#include "Core.h"
#include "Log.h"
#include "Platform/System/SystemManager.h"
#include "ECS/ECS.h"

namespace EM {
	class EM_API Application
	{

	public:


		Application();
		virtual ~Application(); // will be override
		void SystemInput(System* system);
		void Run();				//run the application 
		void End();

	private:
		//SystemManager m_Systems;
		
	};
	 
	//To be defined in CLIENT
	Application* CreateApplication();
}

