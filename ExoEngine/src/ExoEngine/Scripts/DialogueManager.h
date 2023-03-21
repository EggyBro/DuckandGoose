/*!*************************************************************************
****
\file DialogueManager.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Dialogue Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/Graphics/Camera2D.h"

namespace EM
{
	/*!*************************************************************************
	Class for Dialogue Manager Script
	****************************************************************************/
	class DialogueManager : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Dialogue Manager
		****************************************************************************/
		DialogueManager() : mDialogues{ "Dialogue1", "Dialogue2" }, counter{0} {}
		/*!*************************************************************************
		Default destructor for Dialogue Manager
		****************************************************************************/
		~DialogueManager() = default;
		/*!*************************************************************************
		Returns a new copy of Dialogue Manager Script
		****************************************************************************/
		virtual DialogueManager* Clone() const override
		{
			return new DialogueManager(*this);
		}
		/*!*************************************************************************
		Start State of DialogueManager Script
		****************************************************************************/
		virtual void Start() override
		{
			if (p_ecs.HaveComponent<Sprite>(GetScriptEntityID()))
			{
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).is_Animated = false;
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).is_SpriteSheet = false;
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Dialogue1");
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if(p_ecs.HaveComponent<PlayerAttributes>(i))
						p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetPos(p_ecs.GetComponent<Transform>(i).GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - 0.140f);
				}
			}
		}
		/*!*************************************************************************
		Update Loop of DialogueManager Script
		****************************************************************************/
		virtual void Update(float Frametime) override
		{
			UNREFERENCED_PARAMETER(Frametime);
			Entity i{0};
			
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				++counter;
				p_Input->mMouseStatus[GLFW_MOUSE_BUTTON_LEFT] = GLFW_RELEASE;
			}
			if (counter < 2)
			{
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture(mDialogues[counter].c_str());
				for (i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<Logic>(i) && p_ecs.HaveComponent<PlayerAttributes>(i))
					{
						p_ecs.GetComponent<Logic>(i).GetScriptByName("PlayerControl")->mScriptPause = true;
					}
				}
			}
			else
			{
				for (i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<Logic>(i) && p_ecs.HaveComponent<PlayerAttributes>(i))
					{
						p_ecs.GetComponent<Logic>(i).GetScriptByName("PlayerControl")->mScriptPause = false;
					}
				}
				this->mScriptPause = true;
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blank");
			}
		}
		/*!*************************************************************************
		End State for DialogueManager
		****************************************************************************/
		virtual void End() override
		{
			delete this;
		}
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override
		{
			return "DialogueManager";
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		std::string mDialogues[2];
		int counter;
	};
}