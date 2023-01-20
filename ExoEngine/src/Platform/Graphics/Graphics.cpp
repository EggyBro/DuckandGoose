/*!*************************************************************************
****
\file			Graphic.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 /GAM200
\date			9-28-2022
\brief			This file contain a temporarily rendering class which will be bring over
				once render class is up.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
#include "ExoEngine/Math/Math.h"
#include "FrameBuffer.h"
#include "ExoEngine/Timer/Fps.h"
#include "ExoEngine/ECS/SceneManager.h"
namespace EM {

	//extern ECS ecs;
	/*!*************************************************************************
	Load Icon from filepath using resource manager
	****************************************************************************/
	void Graphic::LoadIconsTexture(std::string filename)
	{
		std::ifstream ifs(filename.c_str());
		std::string name, textPath;
		while (ifs >> name >> textPath)
			ResourceManager::LoadIcons(name.c_str(), textPath.c_str());

		ifs.close();
	}

	/*!*************************************************************************
	Load texture from filename using resource manager
	****************************************************************************/
	void Graphic::LoadTexture(std::string filename)
	{
		std::ifstream ifs(filename.c_str());
		std::string name, textPath;
		while (ifs >> name >> textPath)
			ResourceManager::LoadTexture(name.c_str(), textPath.c_str());

		ifs.close();
	}

	//for testing purpose
	/*!*************************************************************************
	Init loop for Graphics
	****************************************************************************/
	void Graphic::Init()
	{
		ResourceManager::LoadShader("QuadShader", "Assets/Shaders/texture.shader");
		ResourceManager::LoadShader("LineShader", "Assets/Shaders/Line.shader");
		ResourceManager::LoadShader("CircleShader", "Assets/Shaders/Circle.shader");
		
	
		LoadIconsTexture("Assets/Text/Icons.txt");
		LoadTexture("Assets/Text/texture.txt");
		
		
		FrameBufferSpecification fbspec;
		fbspec.Attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::DEPTH };
		fbspec.Width = mWinData.GetWidth();
		fbspec.Height = mWinData.GetHeight();
		p_FrameBuffer->SetFrameBufferSpecification(fbspec);
		Renderer::Init();
		mFont->Init();
	}

	/*!*************************************************************************
	Update loop for Graphics
	****************************************************************************/
	void Graphic::Update(float frametime)
	{
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		
		//Resize
		if (FrameBufferSpecification spec = p_FrameBuffer->GetSpecification();
			p_Editor->mViewportSize.x > 0.0f && p_Editor->mViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != p_Editor->mViewportSize.x || spec.Height != p_Editor->mViewportSize.y)
			&& p_Editor->is_ShowWindow)
		{
			p_FrameBuffer->Resize((uint32_t)p_Editor->mViewportSize.x, (uint32_t)p_Editor->mViewportSize.y);
			camera.Resize(p_Editor->mViewportSize.x, p_Editor->mViewportSize.y);
		}
		
	
		mRenderer->ResetInfo();
		mRenderer->Clear();
		if (p_Editor->is_ShowWindow)
		{
			p_FrameBuffer->Bind();
			glClearTexImage(p_FrameBuffer->GetColorAttachmentRendererID(1), 0, GL_RED_INTEGER, GL_INT, 0);
		}
		
		mRenderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		mRenderer->Clear();
		mRenderer->Begin(camera);// begin of the renderer 
		p_GUI->VPmat = camera.GetViewProjectionMatrix();
		

		for (auto const& entity : mEntities)
		{
			auto& transform = p_ecs.GetComponent<Transform>(entity);
			auto& sprite = p_ecs.GetComponent<Sprite>(entity);
			if (sprite.is_Animated)
			{
				mAimator.AddFrameInfo(p_ecs.GetComponent<Sprite>(entity));
				mAimator.UpdateAnimation(frametime);
			}
			if (sprite.is_SpriteSheet)
			{
				mIndex1 = SpriteRender::CreateSprite(GETTEXTURE(sprite.GetTexture()), { sprite.GetIndex().x, sprite.GetIndex().y }, 
					{sprite.GetUVCoor().x, sprite.GetUVCoor().y});

				mRenderer->DrawSprite({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y },
					transform.GetRot(), mIndex1);
			}
			else
			{
				mRenderer->DrawQuad({ transform.GetPos().x, transform.GetPos().y }, { transform.GetScale().x, transform.GetScale().y },
					 transform.GetRot(),GETTEXTURE(sprite.GetTexture()));
			}

			if (p_Editor->mDebugDraw)
			{
				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::rect) && (p_ecs.GetComponent<Collider>(entity).GetAlive()))
				{
					auto& collider = p_ecs.GetComponent<Collider>(entity);
					mRenderer->DrawRect({ transform.GetPos().x + collider.GetOffset().x , transform.GetPos().y + collider.GetOffset().y, 0.0f },
						{ collider.GetMin().x - collider.GetMax().x , collider.GetMin().y - collider.GetMax().y },
						{ 1.0f, 0.0f, 0.0f,1.0f });
				}

				/*if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::line))
					mRenderer->DrawLine({ transform.GetPos().x + collider.GetOffset().x, transform.GetPos().y + collider.GetOffset().y, 0.0f },
						{ (transform.GetPos().x + (25 * velocity.GetVel().x)), (transform.GetPos().y + (25 * velocity.GetVel().y)),0.0f },
						{ 0.0f, 1.0f, 0.0f, 1.0f });*/

				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::circle) && (p_ecs.GetComponent<Collider>(entity).GetAlive()))
				{
					auto& collider = p_ecs.GetComponent<Collider>(entity);
					glm::mat4 Transform = glm::translate(glm::mat4(1.0f), { transform.GetPos().x + collider.GetOffset().x, transform.GetPos().y + collider.GetOffset().y, 0.0f }) *
						glm::scale(glm::mat4(1.0f), glm::vec3(collider.GetRad() * 2));
					mRenderer->DrawCircle(Transform, { 0.5f,0.4f,1.0f, 1.0f }, 0.01f);
				}
			}
			if (p_Editor->selectedEntity == entity && p_Editor->is_ShowWindow)
			{
				auto& trans = p_ecs.GetComponent<Transform>(p_Editor->selectedEntity);
				mRenderer->DrawRect({ trans.GetPos().x , trans.GetPos().y, 0.0f },
					{trans.GetScale().x/2.0f, trans.GetScale().y/2.0f},
					{ 1.0f, 0.0f, 1.0f,1.0f });
			}
		}

		for (auto const& entity : mEntities)
		{
			if (p_ecs.HaveComponent<Tag>(entity) && p_ecs.GetComponent<Tag>(entity).GetTag() == "Player")
				camera.SetPosition({ p_ecs.GetComponent<Transform>(entity).GetPos().x,
					p_ecs.GetComponent<Transform>(entity).GetPos().y,
					0.0f });
		}

		p_Editor->mGameMousePosition = ImGui::GetMousePos();

		p_Editor->mGameMousePosition.x -= p_Editor->mViewportBounds[0].x;
		p_Editor->mGameMousePosition.y -= p_Editor->mViewportBounds[0].y;

		glm::vec2 vpSize{ 0.0f ,0.0f };
		vpSize.x = p_Editor->mViewportBounds[1].x - p_Editor->mViewportBounds[0].x;
		vpSize.y = p_Editor->mViewportBounds[1].y - p_Editor->mViewportBounds[0].y;
		p_Editor->mGameMousePosition.y = vpSize.y - p_Editor->mGameMousePosition.y;

		p_Editor->mGameMousePosition.x = ((p_Editor->mGameMousePosition.x / p_Editor->mViewportSize.x) * 2.0f) - 1.0f;
		p_Editor->mGameMousePosition.y = ((p_Editor->mGameMousePosition.y / p_Editor->mViewportSize.y) * 2.0f) - 1.0f;
		p_Editor->mGameMousePosition.x *= camera.GetZoomLevel();
		p_Editor->mGameMousePosition.y *= camera.GetZoomLevel();

		if (p_GUI->check_pause() == true)
		{
			//UI background
			mRenderer->DrawQuad({ camera.GetPosition().x, camera.GetPosition().y}, { 3.52f, 1.89f }, 0.0f, GETTEXTURE("EndGameUI"));
			mRenderer->DrawQuad({ camera.GetPosition().x + -0.89f, camera.GetPosition().y + -0.01f }, { 1.21f, 1.54f }, 0.0f, GETTEXTURE("Avatar"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.522f, camera.GetPosition().y + 0.118f }, { 1.125f, 1.222f }, 0.0f, GETTEXTURE("MenuPanel"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.526f,camera.GetPosition().y + 0.361f }, { 0.802f, 0.123f }, 0.0f, GETTEXTURE("ResumeButton"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.526f, camera.GetPosition().y + 0.186f }, { 0.802f, 0.123f }, 0.0f, GETTEXTURE("ResumeButton"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.526f, camera.GetPosition().y + -0.007f }, { 0.802f, 0.123f }, 0.0f, GETTEXTURE("ResumeButton"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.526f, camera.GetPosition().y + -0.198f }, { 0.802f, 0.123f }, 0.0f, GETTEXTURE("ResumeButton"));
			mRenderer->DrawQuad({ camera.GetPosition().x + 0.526f, camera.GetPosition().y + -0.556f }, { 1.350f, 0.175f }, 0.0f, GETTEXTURE("ResumeButton"));

		}
		mRenderer->End();
	
		p_FrameBuffer->UnBind();
		
		
		if (p_GUI->check_pause() == true)
		{
			mFont->RenderText("VOLUME", { camera.GetPosition().x + 0.326f, camera.GetPosition().y + 0.321f }, 
				0.002f, camera, { 0.87f, 0.92f, 0.18f });//render the text for the continue button

			mFont->RenderText("CONTROL", { camera.GetPosition().x + 0.296f, camera.GetPosition().y + 0.156f },
				0.002f, camera, { 0.87f, 0.92f, 0.18f });//render the text for the first button

			mFont->RenderText("MAIN MENU", { camera.GetPosition().x + 0.236f, camera.GetPosition().y + -0.037f }, 0.002f, camera, { 0.87f, 0.92f, 0.18f });//to render text for the quit button
			
			mFont->RenderText("QUIT", { camera.GetPosition().x + 0.426f, camera.GetPosition().y + -0.24f }, 0.002f, camera, { 0.87f, 0.92f, 0.18f });//to render text for the quit button
			
			mFont->RenderText("RESUME", { camera.GetPosition().x + 0.326f, camera.GetPosition().y + -0.586f }, 0.002f, camera, { 0.87f, 0.92f, 0.18f });//to render text for the quit button

			p_GUI->set_continue_button({ 0.526f, -0.556f }, 1.350f, 0.175f);//assign position and scale into the GUI
			p_GUI->set_pause_button({ 0.526f, -0.198f }, 0.802f, 0.123f);//assign position and scale into the GUI
		}


		if (p_Input->isKeyPressed(GLFW_KEY_ESCAPE) && p_GUI->mPauseSwitch == false)//toggle menu with escape
		{
			p_GUI->mPauseSwitch = true;//set first boolean to true to prevent flickering
			//camera.resetZoomLevel();//reset zoom back to default
			p_GUI->toggle_pause();//set pause to true thus pausing the game
		}
		if (p_Input->KeyReleased(GLFW_KEY_ESCAPE))
		{
			p_GUI->mPauseSwitch = false;//set pause to false, exit pause menu
		}
		
		if (p_Editor->mViewportFocused && p_Editor->is_ShowWindow)
			camera.MouseScrolling();
		

		Timer::GetInstance().Update(Systems::GRAPHIC);
		
		
	}

	/*!*************************************************************************
	End loop for Graphics
	****************************************************************************/
	void Graphic::End()
	{
		ResourceManager::clear();
		Renderer::ShutDown();
	}

}