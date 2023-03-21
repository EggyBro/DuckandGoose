/*!*************************************************************************
****
\file ScenerioScript.cpp
\author Lau Yong Hui
\par DP email:l.yonghui.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 12/01/2023
\brief	Script That act as the Game scene manager when the game is being played

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "../ECS/SceneManager.h"
#include "ScenerioScript.h"


namespace EM {

	ScenerioScript::ScenerioScript() : SelectedScene{""} {}

		void ScenerioScript::Start(){}

		void ScenerioScript::Update(float Frametime)
		{
			UNREFERENCED_PARAMETER(Frametime);
			/*if (SelectedScene != "")
			{
				p_Scene->DeserializeFromFile(SelectedScene);
				SelectedScene = "";
			}*/
			//auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
			//auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
			//auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
			//auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
			//auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
			//auto& btn = p_ecs.GetComponent<Button>(GetScriptEntityID());

			

			//std::cout << btn.CheckIfclicked();
			//if (btn.CheckIfclicked())
			//{
			//	std::cout << "clicked";
			//	p_Scene->setSceneToLoad("Assets/Scene/Level.json");
			//	btn.Toggleclicked();
			//}
			
			

			/*if (GLFW_KEY_2)
			{
				SelectedScene = "Assets/Scene/HowToPlay.json";
			}
			*/
		}

		void ScenerioScript::End()
		{
			delete this;
		}


		IScript* ScenerioScript::Clone() const
		{
			return new ScenerioScript(*this);
		}
		std::string ScenerioScript::GetScriptName()
		{
			return "ScenerioScript";
		}


}