#include "empch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/Graphics/Graphics.h"
#include "ECS/Object.h"
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			EM::Transform t;
			t.Position(5);
			t.Scale(5);
			t.Rotation(5);
			t.SerializeToFile("Transform.json");
			EM::Player p;
			p.SerializeToFile("Player.json");
			//m_shader->Bind();
			m_graphic->Update();
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