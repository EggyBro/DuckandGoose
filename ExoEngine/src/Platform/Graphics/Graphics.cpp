/*!*************************************************************************
****
\file			Graphic.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain a temporarily rendering class which will be bring over
				once render class is up.

****************************************************************************
***/
#include "empch.h"
#include "Graphics.h"
#include "ExoEngine/GUI/GUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/Timer/Time.h"
#include "Platform/LevelEditor/LevelEditor.h"


namespace EM {

	//extern ECS ecs;

	void Graphic::LoadTexture(std::string filename)
	{
		std::ifstream ifs(filename.c_str());
		std::string name, textPath;
		while (ifs >> name >> textPath)
			ResourceManager::LoadTexture(name.c_str(), textPath.c_str());

		ifs.close();
	}

	//for testing purpose
	void Graphic::Init()
	{
		ResourceManager::LoadShader("QuadShader", "Assets/Shaders/texture.shader");
		ResourceManager::LoadShader("LineShader", "Assets/Shaders/Line.shader");
		ResourceManager::LoadShader("CircleShader", "Assets/Shaders/Circle.shader");
		
		LoadTexture("Assets/textures.txt");
		Renderer::Init();
		m_Font->Init();
	}


	void Graphic::Update(float frametime)
	{
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		m_Renderer->ResetInfo();
		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);// begin of the renderer 
		p_GUI->VPmat = camera.GetViewProjectionMatrix();
		//test for rendering texture, line and rectange to be removed
		m_Font->RenderText("Duck and Goose! Quack", { 0.0f, 0.0f }, 0.005f, camera, { 1.0f, -0.5f, 0.8f });
		
			
	
		for (auto const& entity : mEntities)
		{
			auto& transform = p_ecs.GetComponent<Transform>(entity);
			auto& sprite = p_ecs.GetComponent<Sprite>(entity);
			index1 = SpriteRender::CreateSprite(GETTEXTURE(sprite.GetTexture()), { sprite.GetIndex().x, sprite.GetIndex().y });
			m_Renderer->DrawSprite({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y },
				transform.GetRot(), index1);
			if (p_Editor->mDebugDraw)
			{
				m_Renderer->DrawRect({ transform.GetPos().x , transform.GetPos().y, 0.0f }, { transform.GetScale().x, transform.GetScale().y },
				{1.0f, 0.0f, 0.0f,1.0f});
			}
		}

		m_Renderer->End();
		 
		//for testing 
		
		//camera.SetPosition({.GetPos().x, .GetPos().y, 0.0f });
		/*if (p_Input->isKeyPressed(GLFW_KEY_W))
			player.position.y += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_S))
			m_cameraposition.y -= CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_D))
			m_cameraposition.x += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_A))
		{
			player.position.x -= CameraSpeed * frametime;
			
		}*/
		m_Renderer->DrawRect({ 0.0f,0.0f,0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
		if (p_GUI->check_pause() == true)
		{

			m_Renderer->DrawQuad({ m_cameraposition.x+0.0f, m_cameraposition.y+0.5f,0.0f }, { 1.0f, 0.2f }, { 0.3f, 0.4f, 0.5f, 1.0f });//to create the continue button
			p_GUI->set_continue_button({ 0.0f,0.5f }, 1.0f, 0.2f);//assign position and scale into the GUI
			//std::cout << m_cameraposition.x + 0.0f << " " << m_cameraposition.y + 0.5f << std::endl;
			m_Renderer->DrawQuad({ m_cameraposition.x+0.0f, m_cameraposition.y-0.0f,0.0f }, { 1.0f, 0.2f }, { 0.3f, 0.4f, 0.5f, 1.0f });//to create the quit button 
			p_GUI->set_pause_button({ 0.0f,0.0f }, 1.0f, 0.2f);//assign position and scale into the GUI
			
		}
							 
			
		m_Renderer->End(); 
		if (p_GUI->check_pause() == true)
		{
			m_Font->RenderText("Continue", { m_cameraposition.x - 0.2f , m_cameraposition.y + 0.5f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//render the text for the continue button
			m_Font->RenderText("Quit", { m_cameraposition.x - 0.1f , m_cameraposition.y + 0.0f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//render the text for the first button
			m_Font->RenderText("Game Paused", { m_cameraposition.x - 0.32f , m_cameraposition.y + 0.7f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//to render text for the quit button
		}
																																		
		camera.SetPosition({ m_cameraposition.x, m_cameraposition.y, 0.0f });
		if (p_GUI->check_pause() == false)//if pause restrict movement input
		{
			if (p_Input->isKeyPressed(GLFW_KEY_W))
				m_cameraposition.y += CameraSpeed * frametime;
			if (p_Input->isKeyPressed(GLFW_KEY_S))
				m_cameraposition.y -= CameraSpeed * frametime;
			if (p_Input->isKeyPressed(GLFW_KEY_D))
				m_cameraposition.x += CameraSpeed * frametime;
			if (p_Input->isKeyPressed(GLFW_KEY_A))
			{
				m_cameraposition.x -= CameraSpeed * frametime;
			}
		}
		if (p_Input->isKeyPressed(GLFW_KEY_ESCAPE) && p_GUI->pause_switch == false)//toggle menu with escape
		{
			p_GUI->pause_switch = true;//set first boolean to true to prevent flickering
			camera.resetZoomLevel();//reset zoom back to default
			p_GUI->toggle_pause();//set pause to true thus pausing the game
		}
		if (p_Input->KeyReleased(GLFW_KEY_ESCAPE))
		{
			p_GUI->pause_switch = false;//set pause to false, exit pause menu
		}
			
		camera.MouseScrolling();
		
		Timer::GetInstance().Update(Systems::GRAPHIC);
	}
	void Graphic::End()
	{
		ResourceManager::clear();
		Renderer::ShutDown();
	}

}