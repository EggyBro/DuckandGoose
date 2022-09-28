#include "empch.h"
#include "Window.h"
#include "ExoEngine/Input/Input.h"

namespace EM{


	void Window::Init()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			EM_EXO_ASSERT(!glfwInit(), "\aGLFW init has failed - exit project...");
		}
		glfwSetErrorCallback(ErrorCallback);

		//specify the constraints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
		//we are setting window size able toggle
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); 

		//fullscreen
		m_monitor = glfwGetPrimaryMonitor();

		//set initialize window width & height to current (to be set in rapidjson file)
		m_windowData.m_CurrentWidth = m_windowData.m_Width;
		m_windowData.m_CurrentHeight = m_windowData.m_Height;

		//create window
		m_window = glfwCreateWindow(m_windowData.m_CurrentWidth,
			m_windowData.m_CurrentHeight,
			m_windowData.Title.c_str(),
			NULL, NULL);

		if (!m_window)
		{
			std::cout << "Failed to create window !" << std::endl;
			glfwTerminate();
		}

		EM_EXO_INFO("Generating Window {0} : SIZE ({1},{2})", m_windowData.Title, m_windowData.m_Width, m_windowData.m_Height);
	
		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_windowData);

		if(glewInit() != GLEW_OK)
			EM_EXO_ASSERT(!glewInit(), "GLEW init has failed - abort program...");

		//context
		ToggleVsync(true);
		glfwSetWindowSizeCallback(m_window, Window_size_callback);
		glfwSetCursorPosCallback(m_window, Mouseposition_callback);
		glfwSetKeyCallback(m_window, Key_callback);


	}
	void Window::Update()
	{
		/* Poll for and process events */
		glfwPollEvents();
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);
	}
	void Window::End()
	{
		glfwTerminate();
	}
	void Window::ErrorCallback(int error, const char* description)
	{
		EM_EXO_ERROR("GLFW ERROR {0} : {1}", error, description);
	}
	void Window::Window_size_callback(GLFWwindow* window, int width, int height)
	{
		WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
		data.m_Width = width;
		data.m_Height = height;
		glViewport(0, 0, data.m_Width, data.m_Height);
		//EM_EXO_INFO("Window Current Size ({0}, {1})", data.m_Width, data.m_Height);//debug purpose tb removed
	}
	void Window::Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		InputSystem::GetInstance()->SetKeyStatus(key, action);
	}
	void Window::Mousebutton_callback(GLFWwindow* window, int button, int action, int mode)
	{
		InputSystem::GetInstance()->SetMouseStatus(button, action);
	}
	void Window::Mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	
	}
	void Window::Mouseposition_callback(GLFWwindow* window, double xpos, double ypos)
	{
		WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
		data.mouseX = xpos;
		data.mouseY = ypos;

		//EM_EXO_INFO("Mouse Current Position(x:{0}, y:{1})", data.mouseX, data.mouseY);//debug purpose tb removed
	}
	void Window::ToggleVsync(bool value)
	{
		if (value)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_windowData.Vsync = value;
	}
}