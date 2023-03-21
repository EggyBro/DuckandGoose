/*!*************************************************************************
****
\file Input.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2400 / GAM200
\par Section: a
\date 9-28-2022
\brief  header file for Input.cpp

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "ExoEngine/Core.h"

#define p_Input EM::InputSystem::GetInstance()

namespace EM {

	template class EM_API std::vector <int, std::allocator<int>>;
	template class EM_API std::unordered_map<int, int, std::hash<int>, std::equal_to<int>, std::allocator<std::pair<const int, int>>>;

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
		std::unordered_map<keycode, keystatus> mKeyStatus;
		std::unordered_map<mousecode, mousestatus> mMouseStatus;
		std::vector<keycode> mReset;
		
		double mMouseScrollStatus = 0.0f;
		
	};
}
