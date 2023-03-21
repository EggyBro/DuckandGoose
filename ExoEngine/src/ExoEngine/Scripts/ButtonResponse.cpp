/*!*************************************************************************
****
\file ButtonResponse.cpp
\author Lau Yong Hui
\par DP email:l.yonghui.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM250
\date 20/01/2023
\brief	Script That allow buttons to work when selected and clicked on

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#include "empch.h"
#include "ButtonResponse.h"
#include "../ECS/SceneManager.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/Graphics/Graphics.h"


namespace EM
{

	void ButtonResponse::Start()
	{	
	}

	/*transform.GetPos().x + collider.GetOffset().x , transform.GetPos().y + collider.GetOffset().y, 0.0f },
						{ collider.GetMin().x - collider.GetMax().x , collider.GetMin().y - collider.GetMax().y },
						{ 1.0f, 0.0f, 0.0f,1.0f });*/
	
	void ButtonResponse::Update(float Frametime)
	{
		
		Graphic::camera.SetPosition({ 0.0f,0.0f,0.0f });
		UNREFERENCED_PARAMETER(Frametime);
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		//auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		auto& ID_tag = p_ecs.GetComponent<Tag>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		auto& spt = p_ecs.GetComponent<Sprite>(GetScriptEntityID());
		//Graphic::mcamera->SetZoomLevel(1.0f);
		//Graphic::camera.SetPosition({ 0.0f, 0.0f, 0.0f });
		if (spt.GetTexture() == "HowToPlay" && p_Input->KeyPressed(GLFW_KEY_ESCAPE))
		{

			spt.SetTexture("htp_button_Idle");
			transform.SetPos({ 0.0f,-0.25f });
			transform.SetScale(1.0f, 0.2f);
			p_GUI->toggle_HTP();
		}

		if ( p_GUI->Check_HTP() == false)
		{ 
			
			if (curr_state != button_state::click)
				curr_state = button_state::idle;

		
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::idle)
			{
				curr_state = button_state::click;
			}

			else if (p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::click)
			{
				curr_state = button_state::release;
			}
		
			/*std::cout << ID_tag.GetTag() << ": ";
			if (curr_state == click)
				std::cout << "click\n";
			else if (curr_state == idle)
				std::cout << "idle\n";
			else if (curr_state == release)
				std::cout << "release\n"; */
		}

		if (is_within_box(p_GUI->MousePosition, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
		{
			if (ID_tag.GetTag() == "Start" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Start_Hover");
			}

			if (ID_tag.GetTag() == "Quit" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Quit_Hover");
			}

			if (ID_tag.GetTag() == "Options" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Options_Hover");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("htp_button_Hover");
				//std::cout << "hello";
			}

			if (ID_tag.GetTag() == "MainMenu" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("MM_B");
				//std::cout << "hello";
			}

			if (ID_tag.GetTag() == "Restart" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("RESTART_B");
				//std::cout << "hello";
			}

			if (ID_tag.GetTag() == "Resume" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Resume_Hover");
				//std::cout << "hello";
			}

			if (ID_tag.GetTag() == "PRestart" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Restart_Hover");
				//std::cout << "hello";
			}


			//std::cout << tag.GetNameTag();
			//std::cout << "minX: " << (col[0].mMin.x + transform.GetPos().x)<< "minY: " << (col[0].mMin.y + transform.GetPos().y) << "MaxX: " << (col[0].mMax.x + transform.GetPos().x) << "MaxY: " << (col[0].mMax.y + transform.GetPos().y) << std::endl;
			
			

		
			
			if (curr_state == button_state::release)
			{
				if (ID_tag.GetTag() == "Start" && p_GUI->Check_HTP() == false)
				{
				
					Graphic::mcamera->SetZoomLevel(0.25f);
					p_Scene->setSceneToLoad("Assets/Scene/CutScene.json");
				}

				//f (ID_tag.GetTag() == "Resume")
					//		{
					//			spt.SetTexture("Resume_Idle");
					//		//	transform.SetPos(offset.x + camPos.y, offset.y + camPos.y);
					//		}

				if (ID_tag.GetTag() == "Restart" )
				{
					
					p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
				}

				if (ID_tag.GetTag() == "Quit" && p_GUI->Check_HTP() == false)
				{
					//spt.SetTexture("Quit_Click");
					p_GUI->toggle_script();
				}

				if (ID_tag.GetTag() == "HowToPlay" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("HowToPlay");
					//spt.SetTexture("HowToPlay");
					transform.SetScale({ 4.170206546783447f,1.9999960660934448f });
					transform.SetPos({ 0.0f,0.0f });
					p_GUI->toggle_HTP();
				}

				if (ID_tag.GetTag() == "Options" && p_GUI->Check_HTP() == false)
				{
					p_Scene->setSceneToLoad("Assets/Scene/Option.json");
				}

				if (ID_tag.GetTag() == "MainMenu" && p_GUI->Check_HTP() == false)
				{
					//spt.SetTexture("Start_Click");
					p_GUI->toggle_menu();
					p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
				}
				if (ID_tag.GetTag() == "PResart")
				{
					//p_GUI->toggle_pause();
				
					Graphic::mcamera->SetZoomLevel(0.25f);
					p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
				}

			
			}

			if (curr_state == button_state::click)
			{
				if (ID_tag.GetTag() == "Start" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("Start_Click");
				}

				if (ID_tag.GetTag() == "Quit" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("Quit_Click");
				}

				if (ID_tag.GetTag() == "MainMenu" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("MM_R");

				}

				if (ID_tag.GetTag() == "Restart" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("RESTART_R");

				}

				if (ID_tag.GetTag() == "HowToPlay")
				{
					spt.SetTexture("htp_button_Click");
				}

				if (ID_tag.GetTag() == "Options" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("Options_Click");
				}

				if (ID_tag.GetTag() == "Resume")
				{
					spt.SetTexture("Resume_Click");
					
				}
				if (ID_tag.GetTag() == "PRestart")
				{
					spt.SetTexture("Restart_Click");//to be change
				}
				
			}

			
		}
		else
		{
			if (ID_tag.GetTag() == "Start")
			{
				spt.SetTexture("Start_Idle");
			}

			if (ID_tag.GetTag() == "Quit")
			{
				spt.SetTexture("Quit_Idle");
			}
			if (ID_tag.GetTag() == "Options")
			{
				spt.SetTexture("Options_Idle");
			}

			if (ID_tag.GetTag() == "MainMenu")
			{
				spt.SetTexture("MM_Y");
			}

			if (ID_tag.GetTag() == "Restart")
			{
				spt.SetTexture("RESTART_Y");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay")
			{
				spt.SetTexture("htp_button_Idle");
			}

			if (ID_tag.GetTag() == "Resume")
						{
							spt.SetTexture("Resume_Idle");
						//	transform.SetPos(offset.x + camPos.y, offset.y + camPos.y);
						}
			if (ID_tag.GetTag() == "PRestart")
						{
							spt.SetTexture("Restart_Idle");//to be change
							//transform.SetPos(offset.x + camPos.x, offset.y + camPos.y);
						}



			
		}
			
	}

	void ButtonResponse::End()
	{
		delete this;
	}

	ButtonResponse* ButtonResponse::Clone() const
	{
		return new ButtonResponse(*this);
	}

	
	std::string ButtonResponse::GetScriptName()
	{
		return "ButtonResponse";
	}

	bool ButtonResponse::is_within_box(glm::vec2 cur, Collider box, Transform trans)
	{
		if (cur.x  > ((box[0].mMin.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y > (box[0].mMin.y * (trans.GetScale().y / 2) + trans.GetPos().y) &&
			cur.x  < ((box[0].mMax.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y < (box[0].mMax.y * (trans.GetScale().y / 2) + trans.GetPos().y))
		{
		return true;//return true if the position of the cursor is between both of the button minimun and maximum bounding point
		}
		else
		return false;// return false if it isnt
	}
}

//check if it is menu or play mode
// if play update position of button when pause is toggled on and Hide the UI i