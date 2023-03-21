#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "Platform/Graphics/Camera2D.h"
#include "Platform/Graphics/Graphics.h"
#include "ExoEngine/ECS/SceneManager.h"
#include "ExoEngine/Input/Input.h"

namespace EM
{
	/*!*************************************************************************
	Class for Gate Controller Script
	****************************************************************************/
	class CutScene: public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Gate Controller
		****************************************************************************/
		CutScene() : timer(0), mScenePicker{0} {}
		/*!*************************************************************************
		Default destructor for Gate Controller
		****************************************************************************/
		~CutScene() = default;
		/*!*************************************************************************
		Returns a new copy of GateController Script
		****************************************************************************/
		virtual CutScene* Clone() const override
		{
			return new CutScene(*this);
		}
		/*!*************************************************************************
		Start State of GateController Script
		****************************************************************************/
		virtual void Start() override
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.GetComponent<NameTag>(i).GetNameTag() == "CutScene Controller")
				{
					EM::Graphic::mcamera->SetPosition({ 0.0f, 0.0f, 0.0f });
				}
			}
		}
		/*!*************************************************************************
		Update Loop of GateController Script
		****************************************************************************/
		virtual void Update(float Frametime) override
		{
			timer += Frametime;
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				++mScenePicker;
				EM::Graphic::mcamera->SetPosition({ p_ecs.GetComponent<Transform>(mScenePicker).GetPos().x
					, p_ecs.GetComponent<Transform>(mScenePicker).GetPos().y, 0.0f });
				p_Input->mMouseStatus[GLFW_MOUSE_BUTTON_LEFT] = GLFW_RELEASE;
				timer = 0.0f;
			}
			if (timer >= 5.0f)
			{
				
				++mScenePicker;
				
				EM::Graphic::mcamera->SetPosition({ p_ecs.GetComponent<Transform>(mScenePicker).GetPos().x
					, p_ecs.GetComponent<Transform>(mScenePicker).GetPos().y, 0.0f });
				timer = 0.0f;
			}
			
			if (mScenePicker == 9)
			{
				//transit to another scene
				p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
			}
		}
		/*!*************************************************************************
		End State for GateController
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
			return "CutScene";
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		float timer;
		Entity mScenePicker;
	};
}