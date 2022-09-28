#include "empch.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "LevelEditor.h"

namespace EM {
	std::unique_ptr<LevelEditor> LevelEditor::m_instance{ nullptr };

	std::unique_ptr<LevelEditor>& LevelEditor::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<LevelEditor>();
		}
		return m_instance;
	}
	void LevelEditor::Init(Window* window)
	{
		m_window = window;
		GLFWwindow* m_window = glfwGetCurrentContext();
		glfwMakeContextCurrent(m_window);
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}
	void LevelEditor::Update()
	{
		// Render imgui into screen
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuiIO& io = ImGui::GetIO();
		// tells imgui how big our display is 
		io.DisplaySize = ImVec2(static_cast<float>(m_window->Getter().m_Width), static_cast<float>(m_window->Getter().m_Height));
		ImGui::ShowDemoWindow();
	
	}
	void LevelEditor::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
	/*	GLFWwindow* m_window = glfwGetCurrentContext();
		glfwMakeContextCurrent(m_window);*/
		
	}
	void LevelEditor::End()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	
}