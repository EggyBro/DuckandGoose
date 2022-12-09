/*!*************************************************************************
****
\file			Renderer.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the declaration for Render class which
				has all the necessary draw call for our game.		
****************************************************************************
***/
#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "SpriteRendering.h"
#include "Camera2D.h"

namespace EM {

	class Renderer
	{
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();

		//render call
		static void Init();
		static void ShutDown();

		static void Begin(Camera2D& camera);
		static void End();
		static void Flush();
		

		static void DrawIndexed(const MultiRefs<VertexArray>& vertexarray, unsigned int IndexCount = 0);
		static void DrawForLine(const MultiRefs<VertexArray>& vertexarray, unsigned int vertexCount);

		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::mat4& transform, const MultiRefs<Texture>& texture);

		
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture);
		void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const MultiRefs<Texture>& texture);

		//handle sprite draws
		void DrawSprite(const glm::vec2& position, const glm::vec2& size, const float& rotation, const MultiRefs<SpriteRender>& sprite);
		void DrawSprite(const glm::vec3& position, const glm::vec2& size, const float& rotation, const MultiRefs<SpriteRender>& sprite);
		void DrawSprite(const glm::mat4& transform, const MultiRefs<SpriteRender>& sprite);



		void DrawLine(const glm::vec3& position0, const glm::vec3& position1, const glm::vec4& color);
		void DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float depth = 0.01f, float decline = 0.01f);


		//Information for renderer
		struct Information
		{
			unsigned int n_DrawCalls = 0; //n_ = no. of
			unsigned int n_Quad = 0;

			unsigned int TotalVertexUsed()const { return n_Quad * 4; }
			unsigned int TotalIndexUsed()const { return n_Quad * 6; }
		};
		void ResetInfo();
		static Information GetInfo();
	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static Singleton<SceneData> s_SceneData;

	private:
		static void StartBatch();
		static void NextBatch();
	};
}