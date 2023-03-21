/*!*************************************************************************
****
\file			Gui.h
\author			Lau Yong Hui
\par DP email:	l.yonghui@digipen.edu
\par Course:	Gam200
\section		A
\date			30-10-2022
\brief			This file contain the main function for the pause menu
				and the functions of the buttons. 

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "empch.h"
#include"ExoEngine/Input/Input.h"
#include"ExoEngine/Math/Math.h"
#include "../../Platform/System/System.h"
#include"Platform/Window/Window.h"
#include "ExoEngine/Core.h"
#include <vector>

#define p_GUI EM::gui_system::GetInstance()

namespace EM
{
	

	//bool check_cur_pos();


	class EM_API gui_system 
	{
	private:
		bool is_Pause = { false }; //a boolean to see if the system is currently pause
		bool Script_End = { false };
		bool is_menu = { true };
		bool HTP = { false };

		struct button_bb // a pseudo bounding box not tied to collision meant to check if the cusor is touching the button
		{
			glm::vec2 max{ 0,0 };//top right of the button
			glm::vec2 min{ 0,0 };//buttom left of thr button
		};

		button_bb mPauseButton{}; //bounding box of the pause button (to be replace with factory)
		button_bb mContinueButton{};//bounding box of the continue button (to be replace with factory)
		float mAspectRatio{}; //hold local value of aspecrt ratio
		
	public:
		static std::unique_ptr<gui_system>& GetInstance(); //used to create an instance to work alongside the game during it's lifetime
		glm::vec3 PrevCamPos;
		bool Update(Window* screen); // to be update in realtime  with the rest of the engine system
		bool mPauseSwitch = false; // a secondary boolean to prevent button from flickering 
		glm::mat4 VPmat{}; //hold the viewprojection matrix passed from the camera

		void set_pause_button(vec2D pos, float scaleX, float scaleY); //set the position and scale of the pause button
		void set_continue_button(vec2D pos, float scaleX, float scaleY);//set the position and scale of the continue button
		float Get_AspectRatio() { return mAspectRatio; }//set the position and scale of the continue button
		void toggle_pause();// used to toggle the is_pause boolean
		void toggle_script(){ Script_End = Script_End ? false : true;}//to be used by script
		void toggle_menu() { is_menu = is_menu ? false : true; }
		void toggle_HTP() { HTP = HTP ? false : true; }
		bool check_pause();// a getter function for the pause
		bool Check_script();
		bool Check_menu();
		bool Check_HTP();
		bool is_within_box(glm::vec2 cur, button_bb box);// a helper function to check  if the cursor is touching the button,
		glm::vec2 MousePosition{};
		
		

		//vec2D update_curPos(Window screen);
	};



}
