#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/EventHandler.h"
#include "Platform/System/SystemManager.h"
#include "Platform/Graphics/Shader.h"

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
		SystemManager m_Systems;
		
	
	};
	 
	//To be defined in CLIENT
	Application* CreateApplication();
}

