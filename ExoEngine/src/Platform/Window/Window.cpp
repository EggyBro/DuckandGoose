/*!*************************************************************************
****
\file			Window.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain function that create a window using GLFW library

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Window.h"
#include "ExoEngine/Input/Input.h"
#include "Platform/LevelEditor/LevelEditor.h"
#include "ExoEngine/Timer/Time.h"

namespace EM{

	Window::Window() : m_window{ nullptr }, m_monitor{ nullptr },
		m_windowData{ windowData.GetTitle(), windowData.GetWidth(), windowData.GetHeight(), windowData.GetCurrWidth(), windowData.GetCurrHeight(), 0, 0 },//should be serialized
		m_vsync{ false }, previousTime{glfwGetTime()}, frameCount{0}
	{
		windowData.DeserializeFromFile("Window.json");
		m_windowData.Title = windowData.GetTitle();
		m_windowData.m_Width = windowData.GetWidth();
		m_windowData.m_Height = windowData.GetHeight();
		m_windowData.m_CurrentWidth = windowData.GetCurrWidth();
		m_windowData.m_CurrentHeight = windowData.GetCurrHeight();
		windowData.SerializeToFile("Window.json");
	};

	/*!*************************************************************************
	Init loop of window, uses glfw to set and create window
	****************************************************************************/
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
		glfwSetScrollCallback(m_window, Mousescroll_callback);
		glfwSetMouseButtonCallback(m_window, Mousebutton_callback);
		glfwSetFramebufferSizeCallback(m_window, Window_size_callback);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetDropCallback(m_window, drop_callback);
	}

	/*!*************************************************************************
	Update loop of window
	****************************************************************************/
	void Window::Update(float frametime)
	{
		(void)frametime;
		/* Poll for and process events */
		glfwPollEvents();
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);

	}
  
	/*!*************************************************************************
	End loop of window
	****************************************************************************/
	void Window::End()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	/*!*************************************************************************
	drop_callback function is the function definition for the glfwSetDropCallback
	function parameter to enable drag and drop functionality to drag and drop
	files from external folders to the game engine.  
	****************************************************************************/
	void Window::drop_callback(GLFWwindow* window, int count, const char** paths)
	{
		UNREFERENCED_PARAMETER(window);
		for (int i = 0; i < count; i++)
		{
			if (std::filesystem::path(paths[i]).extension() == ".wav")
			{
				//copy the wav file to metadigger folder
				auto folder = std::filesystem::path("Assets/metadigger");
				auto filename = std::filesystem::path(paths[i]).filename();
				std::filesystem::copy(std::filesystem::path(paths[i]), folder / filename);
				//insert entry into audio file paths
				p_Editor->insertAudioFilePath(paths[i]);
			}

			else if (std::filesystem::path(paths[i]).extension() == ".png")
			{
				auto folder = std::filesystem::path("Assets/Textures");
				auto filename = std::filesystem::path(paths[i]).filename();
				std::filesystem::copy(std::filesystem::path(paths[i]), folder / filename);
				//insert entry into audio file paths
				p_Editor->insertTextureFilePath(paths[i]);
			}
			else
			{
				EM_EXO_INFO("Error Detected The extenstion is {0}", std::filesystem::path(paths[i]).extension().string().c_str());
			}
			//sort by extension
			//use filesystem to copy filepathing to editor
			//use filesystem to copy files into relevant asset folders
		}
	}

	/*!*************************************************************************
	spdlog assert for window error
	****************************************************************************/
	void Window::ErrorCallback(int error, const char* description)
	{
		EM_EXO_ERROR("GLFW ERROR {0} : {1}", error, description);
	}

	/*!*************************************************************************
	Window size callback function
	****************************************************************************/
	void Window::Window_size_callback(GLFWwindow* window, int width, int height)
	{
		WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
		data.m_Width = width;
		data.m_Height = height;
		glViewport(0, 0, data.m_Width, data.m_Height);
		//EM_EXO_INFO("Window Current Size ({0}, {1})", data.m_Width, data.m_Height); //for debug purpose tb removed
	}

	/*!*************************************************************************
	Window key callback function
	****************************************************************************/
	void Window::Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		UNREFERENCED_PARAMETER(window);
		(void)scancode, (void)mode;
		InputSystem::GetInstance()->SetKeyStatus(key, action);
	}

	/*!*************************************************************************
	Window mouse button callback function
	****************************************************************************/
	void Window::Mousebutton_callback(GLFWwindow* window, int button, int action, int mode)
	{
		(void)window, (void)mode;
		InputSystem::GetInstance()->SetMouseStatus(button, action);
	}

	/*!*************************************************************************
	Window mousescroll callback function
	****************************************************************************/
	void Window::Mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		(void)window, (void)xoffset, (void)yoffset;
		InputSystem::GetInstance()->mMouseScrollStatus = static_cast<int>(yoffset);
	}

	/*!*************************************************************************
	Window mouse position callback function
	****************************************************************************/
	void Window::Mouseposition_callback(GLFWwindow* window, double xpos, double ypos)
	{
		
		WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
		data.mouseX = xpos;
		data.mouseY = ypos;

		//EM_EXO_INFO("Mouse Current Position(x:{0}, y:{1})", data.mouseX, data.mouseY);//for debug purpose tb removed
	}

	/*!*************************************************************************
	Toggle vsync function
	****************************************************************************/
	void Window::ToggleVsync(bool value)
	{
		if (value)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_windowData.Vsync = value;
	}
}