/*!*************************************************************************
****
\file LevelEditor.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2400 / GAM200
\date 9-28-2022
\brief  Header file for LevelEditor.cpp
****************************************************************************
***/
#pragma once
#include "Platform/Window/Window.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#define p_Editor EM::LevelEditor::GetInstance()

namespace EM {
	class LevelEditor
	{
	public:
		//ctor and dtor
		LevelEditor() = default;
		~LevelEditor() = default;

		//main function for running
		void Init(Window* window);
		void LoadSceneFromFile(); //Load all the json file into a container for easy access in imgui
		void Update();	//update loop
		void Draw();
		void End();

		void LoadSaveScene();
		void SceneViewer();
		void ContentBrowser();
		void Logger();
		void Profiler();
		void Hierarchy();
		void Inspector();

		//for audio loading from files
		void LoadAudioFromFile();
		void AudioManager();
		void insertAudioFilePath(std::string in);
		void insertTextureFilePath(std::string on);

		//for textures loading from files
		void LoadTextureFromFile();
	public:
		bool show_window = true;
		static std::unique_ptr<LevelEditor>& GetInstance();


		//inspector and Hierarchy
		Entity selectedEntity = {};


		//for inspector and Hierarchy
		bool mDebugDraw{ false }; //to show debug/collision draw 

		//For resize and sceneviewer/viewport
		ImVec2 mViewportSize = { 0.0f, 0.0f };
		ImVec2 mViewportBounds[2];
		bool mViewportFocused = false;
		ImVec2 mGameMousePosition = { 0.0f, 0.0f };
	private:
		void MainMenuBar();
		void Docking();
		bool FullScreenMode{};
		bool Pad{};

	private:
		
		ImGuiDockNodeFlags dock_space_flags{};
		Window* m_window{nullptr};
		static std::unique_ptr<LevelEditor> m_instance;
		

		//profiler
		bool b_profile = false;
		float m_SceneRuntime = 0.0f;
		float m_UpdateTimer = 0.0f;
		std::array<float, 5> mSystemRunTime = { 0.0f,0.0f,0.0f,0.0f };
		
		
	
		//Content Browser
		std::filesystem::path mAssetsPath= "Assets";
		std::filesystem::path m_CurrentDirectory = mAssetsPath;
		
		//Scene/guizmo
		int mGizmoType = -1;
		WinData mwindata;

		//For loading of scene usage
		std::vector<std::string> mScenefile; //json file
		// To keep track of the files
		int mSelectedFile = -1;
		std::vector<std::filesystem::directory_entry> mFileList;
		ImVec4 _gameWindowSpecs;

		//load audio from file
		std::vector<std::string> mAudioFile;
		std::vector<std::filesystem::directory_entry> mAudioFileList;
		//for displaying of audio channels
		
		//load texture from file
		std::vector<std::string> mTextureFile;
		std::vector<std::filesystem::directory_entry> mTextureFileList;
	};
}