#pragma once
#include "ExoEngine.h"
#include "ExoEngine/Core.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace EM {

	//properties used in window
	struct WindowProps 
	{
		std::string Title;
		unsigned int m_Width,
					 m_Height,
					 m_CurrentWidth,
					 m_CurrentHeight;
		bool Vsync;
		double mouseX, mouseY;
	};

	class EM_API Window : public System
	{
	public:
		Window() : m_window{ nullptr }, m_monitor{ nullptr },
			m_windowData{ "Exomata", 1280, 720, 0, 0, 0, 0},//should be serialized
			m_vsync{ false }{};

		~Window() = default;

	public:
		
		//Initialize
		virtual void Init() override;
		//update
		virtual void Update() override;
		//Delete window
		virtual void End() override;

		//Getter
		//Window name
		virtual std::string GetName() override { return m_windowData.Title; }
		WindowProps Getter() const { return m_windowData; }
		GLFWwindow* GetWindow() const { return m_window; }
		GLFWmonitor* GetMonitor() const { return m_monitor; }

	private:
		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;
		WindowProps m_windowData;
		bool m_vsync;

	private:
		// Event callback functions
		static void ErrorCallback(int error, const char* description); // error
		static void Window_size_callback(GLFWwindow* window, int width, int height); // whenever window size changes, this function is called
		static void Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); // key input
		static void Mousebutton_callback(GLFWwindow* window, int button, int action, int mode); // mouse input
		static void Mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset); // mouse scrolling
		static void Mouseposition_callback(GLFWwindow* window, double xpos, double ypos); // mouse position
		
		void ToggleVsync(bool value);// vync based on internal
	};
}