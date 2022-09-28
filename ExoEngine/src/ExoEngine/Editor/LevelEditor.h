#pragma once
#include "Platform/Window/Window.h"


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
		void Update();
		void Draw();
		void End();
	    
		static std::unique_ptr<LevelEditor>& GetInstance();
	private:
		Window* m_window;
		static std::unique_ptr<LevelEditor> m_instance;
	};
}