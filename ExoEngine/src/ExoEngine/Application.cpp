#include "empch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/Graphics/Graphics.h"
#include "Editor/LevelEditor.h"
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
		Window* m_window = new Window;
		m_window->Init();
		m_Systems.SystemIndex(0, m_window); //1st layer window

		//p_Editor->Init(m_window);

		Graphic* m_graphic = new Graphic;
		m_graphic->Init();
		m_Systems.SystemIndex(1, m_graphic);

		while (!glfwWindowShouldClose(m_window->GetWindow()))
		{
			
			m_window->Update();
			m_graphic->Update();
			
			//p_Editor->Update();
			//p_Editor->Draw();
		}

		End();
	}

	

	void Application::End()
	{
		//p_Editor->End();
		m_Systems.DeleteSystem();
	}

}