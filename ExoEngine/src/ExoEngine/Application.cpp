#include "empch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/Graphics/Graphics.h"

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

		Graphic* m_graphic = new Graphic;
		m_graphic->Init();
		m_Systems.SystemIndex(1, m_graphic);

		while (!glfwWindowShouldClose(m_window->GetWindow()))
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//m_shader->Bind();
			m_graphic->Update();
			m_window->Update();
		}

		End();
	}

	

	void Application::End()
	{
		m_Systems.DeleteSystem();
	}

}