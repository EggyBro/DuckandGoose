#include "empch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Window/Window.h"


namespace EM {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::SystemInput(System* system)
	{
		m_Systems.SystemIncrement(system);
		system->Init();
	}

	void Application::Run() 
	{
		//testing event TO BE REMOVED
		WindowResizingEvent e(1280, 720);
		EM_TRACE(e);
		//Window
		Window* window = new Window;
		window->Init();
		m_Systems.SystemIndex(0, window); //1st layer window


		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			window->Update();
		}

		End();
	}

	

	void Application::End()
	{
		m_Systems.DeleteSystem();
	}

}