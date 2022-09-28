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

		//player
		player.position = { -0.1f, 0.1f };
		player.scale = { 0.1f, 0.1f };

		//wall
		wall.position = { 0.1f, 0.1f };
		wall.scale = { 0.1f, 0.1 };
	}
	//testing purpose for now
	//to be fix as now is calling two draw calls
	//need to create a proper rendering calls
	void Graphic::Update()
	{
		m_shader->Bind();
		m_vertexArr->Bind();
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.f), { player.position, 0.0f }) *
				glm::rotate(glm::mat4(1.0f), player.dir, glm::vec3(0.f, 0.f, 1.f)) *
				glm::scale(glm::mat4(1.f), { player.scale, 1.0f });
			m_shader->SetUniform("u_Mvp", transform);
			glDrawElements(GL_TRIANGLES, m_Ibuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
		{
			glm::mat4 transform2 = glm::translate(glm::mat4(1.f), { wall.position, 0.0f }) *
				glm::rotate(glm::mat4(1.0f), wall.dir, glm::vec3(0.f, 0.f, 1.f)) *
				glm::scale(glm::mat4(1.f), { wall.scale, 1.0f });
			m_shader->SetUniform("u_Mvp", transform2);
			glDrawElements(GL_TRIANGLES, m_Ibuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
		if (p_Input->isKeyPressed(GLFW_KEY_W))
		{
			player.position.y += 0.01f;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_S))
		{
			player.position.y -= 0.01f;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_A))
		{
			player.position.x -= 0.01f;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_D))
		{
			player.position.x += 0.01f;
		}
		
		


	}

	void Graphic::End()
	{

	}
	
}