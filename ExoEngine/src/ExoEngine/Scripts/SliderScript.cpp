/*!*************************************************************************
****
\file SliderScript.cpp
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
#include "SliderScript.h"
#include "../ECS/SceneManager.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/LevelEditor/LevelEditor.h"



namespace EM
{

	void SliderScript::Start()
	{
		clicked = false;
		selected = false;
	
		def_position = p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos();
		limit.min = { def_position.x - 0.5f,def_position.y - 0.1f };
		limit.max = { def_position.x+0.5f,def_position.y+0.1f };

	}

	/*transform.GetPos().x + collider.GetOffset().x , transform.GetPos().y + collider.GetOffset().y, 0.0f },
						{ collider.GetMin().x - collider.GetMax().x , collider.GetMin().y - collider.GetMax().y },
						{ 1.0f, 0.0f, 0.0f,1.0f });*/

	void SliderScript::Update(float Frametime)
	{
		UNREFERENCED_PARAMETER(Frametime);
		//things to add check volume and set pos accordingly

		

		if (p_Editor->is_ShowWindow == true || limitset == false)
		{
			//std::cout<< SliderCali;
			if (SliderCali == true)
			{
				
				p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetPos(limit.min.x + 0.5f, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos().y);
				SliderCali = false;//slider have been calibrated
			}
			def_position = p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos();
			limit.min = { def_position.x - 0.5f,def_position.y - 0.1f };
			limit.max = { def_position.x + 0.5f,def_position.y + 0.1f };
			limitset = true;
		}

		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		//auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		auto& ID_tag = p_ecs.GetComponent<Tag>(GetScriptEntityID());
		//auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());

		
		if(p_Editor->is_ShowWindow == false)
		{ 
			if(ID_tag.GetTargetTag()== "Master")
			transform.SetPos(p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup())+limit.min.x, transform.GetPos().y);

			if (ID_tag.GetTargetTag() == "BGM")
				transform.SetPos(p_Audio->GetVolumeByChannel(p_Audio->GetBGMChannelGroup()) + limit.min.x, transform.GetPos().y);

			if (ID_tag.GetTargetTag() == "SFX")
				transform.SetPos(p_Audio->GetVolumeByChannel(p_Audio->GetSFXChannelGroup()) + limit.min.x, transform.GetPos().y);


			SliderCali = true;
			//std::cout << "limit min at:" << limit.min.x;
			if((p_GUI->MousePosition.x >= limit.min.x && p_GUI->MousePosition.y >= limit.min.y) &&
				(p_GUI->MousePosition.x <= limit.max.x&& p_GUI->MousePosition.y <= limit.max.y))//if system is pause and continue button is pressed, tell the system to resume the game
			{
				if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
				{
					clicked = true;
					transform.SetPos(p_GUI->MousePosition.x, transform.GetPos().y);		
				}
				else
				{
					
					clicked = false;
				}
			}

			
			if (ID_tag.GetTargetTag() == "Master")
			{
				p_Audio->SetVolumeByChannel(p_Audio->GetMasterChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				if (p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) < 0.01)
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetMasterChannelGroup(), 0.0f);
				}
				p_Audio->SetVolume(0, 1 / p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) + 1);
				if (p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) < p_Audio->GetVolumeByChannel(p_Audio->GetSFXChannelGroup()))
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetSFXChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				}

				if (p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) < p_Audio->GetVolumeByChannel(p_Audio->GetBGMChannelGroup()))
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetBGMChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				}

			}

			if (ID_tag.GetTargetTag() == "BGM")
			{
				p_Audio->SetVolumeByChannel(p_Audio->GetBGMChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				if (p_Audio->GetVolumeByChannel(p_Audio->GetBGMChannelGroup()) < 0.01)
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetBGMChannelGroup(), 0.0f);
				}
				p_Audio->SetVolume(1, 1 / p_Audio->GetVolumeByChannel(p_Audio->GetBGMChannelGroup()) + 1);

				if (p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) < p_Audio->GetVolumeByChannel(p_Audio->GetBGMChannelGroup()))
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetMasterChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				}
			}

			if (ID_tag.GetTargetTag() == "SFX")
			{
				p_Audio->SetVolumeByChannel(p_Audio->GetSFXChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				if (p_Audio->GetVolumeByChannel(p_Audio->GetSFXChannelGroup()) < 0.01)
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetSFXChannelGroup(), 0.0f);
				}
				p_Audio->SetVolume(2, 1 / p_Audio->GetVolumeByChannel(p_Audio->GetSFXChannelGroup()) + 1);

				if (p_Audio->GetVolumeByChannel(p_Audio->GetMasterChannelGroup()) < p_Audio->GetVolumeByChannel(p_Audio->GetSFXChannelGroup()))
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetMasterChannelGroup(), transform.GetPos().x - limit.min.x / (limit.max.x - limit.min.x));
				}
			}



		}

		if (p_Input->KeyPressed(GLFW_KEY_ESCAPE))
		{
			
				limitset = false;
				p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
			
		}

		
	}

	void SliderScript::End()
	{
		delete this;
	}

	SliderScript* SliderScript::Clone() const
	{
		return new SliderScript(*this);
	}


	std::string SliderScript::GetScriptName()
	{
		return "SliderScript";
	}

	bool SliderScript::is_within_box(glm::vec2 cur, Collider box, Transform trans)
	{
		if (cur.x > ((box[0].mMin.x * (trans.GetScale().x / 2)) + trans.GetPos().x) && cur.y > (box[0].mMin.y * (trans.GetScale().y / 2) + trans.GetPos().y) &&
			cur.x < ((box[0].mMax.x * (trans.GetScale().x / 2)) + trans.GetPos().x) && cur.y < (box[0].mMax.y * (trans.GetScale().y / 2) + trans.GetPos().y))
		{
			return true;//return true if the position of the cursor is between both of the button minimun and maximum bounding point
		}
		else
			return false;// return false if it isnt
	}
}