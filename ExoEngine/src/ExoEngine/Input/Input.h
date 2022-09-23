#pragma once
#include "ExoEngine/Core.h"


namespace EM {

	using keystatus = int;
	using keycode = int;
	using mousestatus = int;
	using mousecode = int;


	class EM_API InputSystem
	{
	public:
		//Pointer to input system
		static std::unique_ptr<InputSystem>& GetInstance();

		// key inputs 
		bool KeyPressed(const int& key);
		bool KeyHold(const int& key);
		bool KeyReleased(const int& key);

		void SetKeyStatus(keycode key, keystatus status);
		void ResetPressedKey();

		//mouse inputs
		bool MousePressed(const int& key);
		bool MouseHold(const int& key);
		bool MouseIsReleased(const int& key);

		void SetMouseStatus(mousecode key, mousestatus status);
		void ResetPressedMouse();

		bool isKeyPressed(keycode key);

	public:
		//data
		std::unordered_map<keycode, keystatus> m_KeyStatus;
		std::unordered_map<mousecode, mousestatus> m_MouseStatus;
		std::vector<keycode> m_reset;
		
		
	};
}
