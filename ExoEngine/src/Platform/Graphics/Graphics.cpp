#include "empch.h"
#include "Graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ExoEngine/Input/Input.h"
#include <GLFW/glfw3.h>

namespace EM {

	//for testing purpose
	void Graphic::Init()
	{
		m_shader.reset(new Shader("Assets/Shaders/basic.shader"));


		m_vertexArr.reset(VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, //per vertex->
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};
		m_Vbuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));
		
		m_vertexArr->AddVertexBuffer(m_Vbuffer);

		unsigned int indices[] = { 0, 1, 2,
								   2, 3, 0};
		m_Ibuffer.reset(new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
		m_vertexArr->SetIndexBuffer(m_Ibuffer);

		player.m_Transform.SetPos(vec2D(-0.1f, 0.1f));
		player.m_Transform.SetScale(vec2D(0.1f, 0.1f));
		player.m_Transform.SerializeToFile("PlayerTransform.json");

		
		player.m_RigidBody.SetMin(vec2D(-0.5f,-0.5f) *= player.m_Transform.GetScale());
		player.m_RigidBody.SetMin(player.m_RigidBody.GetMin() += player.m_Transform.GetPos());
		player.m_RigidBody.SetMax(vec2D(0.5f, 0.5f) *= player.m_Transform.GetScale());
		player.m_RigidBody.SetMax(player.m_RigidBody.GetMax() += player.m_Transform.GetPos());
		player.m_RigidBody.SetVel(vec2D(0.01f, 0.01f));
		player.m_RigidBody.SetInitVel(player.m_RigidBody.GetVel());
		player.m_RigidBody.SerializeToFile("PlayerAABB.json");


		//wall
		wall.m_Transform.SetPos(vec2D(0.1f, 0.1f));
		wall.m_Transform.SetScale(vec2D(0.1f, 0.1f));
		wall.m_Transform.SerializeToFile("WallTransform.json");

		wall.m_RigidBody.SetMin(vec2D(-0.5f, -0.5f) *= wall.m_Transform.GetScale());
		wall.m_RigidBody.SetMin(wall.m_RigidBody.GetMin() += wall.m_Transform.GetPos());
		wall.m_RigidBody.SetMax(vec2D(0.5f, 0.5f) *= wall.m_Transform.GetScale());
		wall.m_RigidBody.SetMax(wall.m_RigidBody.GetMax() += wall.m_Transform.GetPos());
		wall.m_RigidBody.SetVel(vec2D(0.0f, 0.0f));
		wall.m_RigidBody.SetInitVel(wall.m_RigidBody.GetVel());
		wall.m_RigidBody.SerializeToFile("WallAABB.json");

		
	}
	//testing purpose for now
	//to be fix as now is calling two draw calls
	//need to create a proper rendering calls

	void Graphic::Update()
	{
		//player
		player.m_Transform.DeserializeFromFile("PlayerTransform.json");
		player.m_RigidBody.DeserializeFromFile("PlayerAABB.json");

		player.m_RigidBody.SetMin(vec2D(-0.5f, -0.5f) *= player.m_Transform.GetScale());
		player.m_RigidBody.SetMin(player.m_RigidBody.GetMin() += player.m_Transform.GetPos());
		player.m_RigidBody.SetMax(vec2D(0.5f, 0.5f) *= player.m_Transform.GetScale());
		player.m_RigidBody.SetMax(player.m_RigidBody.GetMax() += player.m_Transform.GetPos());

		if (m_IsColliding.boundingBoxCollision(player.m_RigidBody.GetMax(), player.m_RigidBody.GetMin(), player.m_RigidBody.GetVel()
			, wall.m_RigidBody.GetMax(), wall.m_RigidBody.GetMin(), wall.m_RigidBody.GetVel()))
		{
			player.m_RigidBody.SetVel(vec2D(-(player.m_RigidBody.GetVel().value.x) - 0.01f, -(player.m_RigidBody.GetVel().value.y) - 0.01f));
			player.m_Transform.GetPos().value.x -= 0.001f;
			player.m_Transform.GetPos().value.y -= 0.001f;
		}
		else
		{
			player.m_RigidBody.SetVel(player.m_RigidBody.GetInitVel());
		}

			if (p_Input->isKeyPressed(GLFW_KEY_W))
			{
				player.m_Transform.GetPos().value.y += player.m_RigidBody.GetVel().value.y;
			}
			if (p_Input->isKeyPressed(GLFW_KEY_S))
			{
				player.m_Transform.GetPos().value.y -= player.m_RigidBody.GetVel().value.y;
			}
			if (p_Input->isKeyPressed(GLFW_KEY_A))
			{
				player.m_Transform.GetPos().value.x -= player.m_RigidBody.GetVel().value.x;
			}
			if (p_Input->isKeyPressed(GLFW_KEY_D))
			{
				player.m_Transform.GetPos().value.x += player.m_RigidBody.GetVel().value.x;
			}


		m_shader->Bind();
		m_vertexArr->Bind();
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.f), { player.m_Transform.GetPos().value.x, player.m_Transform.GetPos().value.y, 0.0f }) *
				glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.f, 0.f, 1.f)) *
				glm::scale(glm::mat4(1.f), { player.m_Transform.GetScale().value.x, player.m_Transform.GetScale().value.y, 1.0f });
			m_shader->SetUniform("u_Mvp", transform);
			glDrawElements(GL_TRIANGLES, m_Ibuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
		{
			glm::mat4 transform2 = glm::translate(glm::mat4(1.f), { wall.m_Transform.GetPos().value.x, wall.m_Transform.GetPos().value.y, 0.0f }) *
				glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.f, 0.f, 1.f)) *
				glm::scale(glm::mat4(1.f), { wall.m_Transform.GetScale().value.x,wall.m_Transform.GetScale().value.y, 1.0f });
			m_shader->SetUniform("u_Mvp", transform2);
			glDrawElements(GL_TRIANGLES, m_Ibuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

		player.m_Transform.SerializeToFile("PlayerTransform.json");
		player.m_RigidBody.SerializeToFile("PlayerAABB.json");

	}

	void Graphic::End()
	{

	}
	
}