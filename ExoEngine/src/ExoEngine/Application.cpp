/*!*************************************************************************
****
\file			Application.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			9-28-2022
\brief			This file contain the main game loop

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Application.h"
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/LevelEditor/LevelEditor.h"
#include "Platform/Graphics/Graphics.h"
#include "Platform/Physics/CollisionSystem.h"
#include "Platform/Physics/PhysicsSystem.h"
#include "ECS/Components/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneManager.h"
#include "Audio/AudioEngine.h"
#include "ExoEngine/Scripts/PlayerController.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "Platform/Logic/LogicSystem.h"
#include "ExoEngine/Scripts/EnemyMovement.h"
#include "ExoEngine/GUI/GUI.h"


namespace EM {
	bool end_state{false}; //placeholder

/*!*************************************************************************
Application constructor
****************************************************************************/
	Application::Application()
	{
		p_ecs.Init();
		p_Scene->Init();
		FramePerSec::GetInstance().InitFrame();
	}

/*!*************************************************************************
Application destructor
****************************************************************************/
	Application::~Application()
	{
	}

/*!*************************************************************************
System input
****************************************************************************/
	void Application::SystemInput(System* system)
	{
		(void)system;
	}

/*!*************************************************************************
Run loop for application
****************************************************************************/
	void Application::Run() 
	{
		Timer::GetInstance().GlobalTimeStarter();
		
		Window* m_window = new Window;
		m_window->Init();
		p_Audio->Init();
		p_Editor->Init(m_window);

		auto mGraphics = p_ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<Sprite>());
			p_ecs.SetSystemSignature<Graphic>(signature);
		}
		mGraphics->Init();

		auto mPosUpdate = p_ecs.RegisterSystem<PhysicsSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			p_ecs.SetSystemSignature<PhysicsSystem>(signature);
		}
		mPosUpdate->Init();

		auto mLogic = p_ecs.RegisterSystem<LogicSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Logic>());
			p_ecs.SetSystemSignature<LogicSystem>(signature);
		}
		mLogic->Init();

		auto mCollision = p_ecs.RegisterSystem<CollisionSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			signature.set(p_ecs.GetComponentType<Collider>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			p_ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();

		//FOR DEBUGGING ECS 
		//Scene Manager Requires some tweaking to entity serialization and deserialization
		//RigidBody rb;
		//Logic logic;
		//Sprite sprite;
		//NameTag name;
		//Tag tag;

		//Entity Background = p_ecs.CreateEntity();
		//name.SetNameTag("BackGround");
		//p_ecs.AddComponent<NameTag>(Background, name);
		//p_ecs.AddComponent<Transform>(Background, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Background, SpriteComponent);
		//p_ecs.AddComponent<RigidBody>(Background, rb);
		//p_ecs.AddComponent<Collider>(Background, ColliderComponent);
		//p_ecs.AddComponent<Tag>(Background, TagComponent);
		//p_ecs.AddComponent<Logic>(Background, LogicComponent);

		//Entity player = p_ecs.CreateEntity();
		//name.SetNameTag("Player");
		//sprite.SetTexture("Idle");
		//p_ecs.AddComponent<Transform>(player, C_TransformComponent);
		//p_ecs.AddComponent<RigidBody>(player, rb);
		//p_ecs.AddComponent<Sprite>(player, sprite);
		//p_ecs.AddComponent<NameTag>(player, name);
		//p_ecs.AddComponent<Collider>(player, ColliderComponent);
		//tag.SetTag("Player");
		//p_ecs.AddComponent<Tag>(player, tag);
		//p_ecs.AddComponent<Logic>(player, logic);	//Add Component
		//p_ecs.GetComponent<Logic>(player).InsertScript(new PlayerController(), player);
		//p_ecs.GetComponent<Logic>(player).InsertScript(new CollisionResponse(), player);


		//Entity enemy = p_ecs.CreateEntity();
		//Logic logic2;
		//p_ecs.AddComponent<Transform>(enemy, C_TransformComponent);
		//p_ecs.AddComponent<RigidBody>(enemy, rb);
		//p_ecs.AddComponent<Sprite>(enemy, sprite);
		//p_ecs.AddComponent<Collider>(enemy, ColliderComponent);
		//p_ecs.AddComponent<Tag>(enemy, TagComponent);
		//p_ecs.AddComponent<NameTag>(enemy, NameTagComponent);
		//p_ecs.GetComponent<NameTag>(enemy).SetNameTag("Enemy");
		//p_ecs.AddComponent<Logic>(enemy, logic2);
		//p_ecs.GetComponent<Logic>(enemy).InsertScript(new EnemyMovement(), enemy);
		//p_ecs.GetComponent<Logic>(enemy).InsertScript(new CollisionResponse(), enemy);

		//Entity col = p_ecs.CreateEntity();
		//p_ecs.AddComponent<Tag>(col, TagComponent);
		//p_ecs.GetComponent<Tag>(col).SetTag("PlayerAttack");
		//p_ecs.GetComponent<Tag>(col).SetTargetTag("Enemy");
		//p_ecs.AddComponent<Sprite>(col, SpriteComponent);
		//p_ecs.AddComponent<Transform>(col, C_TransformComponent);
		//p_ecs.GetComponent<Transform>(col).SetComponentEntityID(player);
		//p_ecs.GetComponent<Transform>(col).GetComponentEntityID();
		//p_ecs.AddComponent<RigidBody>(col, rb);
		//p_ecs.AddComponent<NameTag>(col, name);
		//p_ecs.GetComponent<NameTag>(col).SetNameTag("PlayerAttackCollider");
		//p_ecs.AddComponent<Collider>(col, ColliderComponent);
		//p_ecs.AddComponent<Logic>(col, LogicComponent);
		
		while (!glfwWindowShouldClose(m_window->GetWindow()) && end_state == false) //game loop
		{
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);

			if (p_GUI->check_pause() == false)
			{
				p_Audio->Update();
				p_Editor->Update();
				if (p_Editor->is_ShowWindow)
				{
					p_Editor->Draw();
				}
				mLogic->Update(Timer::GetInstance().GetGlobalDT());
				mPosUpdate->Update();
				mCollision->Update(Timer::GetInstance().GetGlobalDT());
			}
			end_state = p_GUI->Update(m_window);

			p_Input->ResetPressedKey();//to fix the buggy error from glfwpollevent

			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
		
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
			
		}
		mLogic->End();
		End();
	}

/*!*************************************************************************
End loop for application
****************************************************************************/
	void Application::End()
	{
		//p_Scene->SerializeToFile("Assets/Scene/Level.json");
		p_Editor->End();
		p_Audio->Release();
	}
}