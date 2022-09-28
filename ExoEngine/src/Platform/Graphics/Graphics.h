#pragma once
#include "Platform/System/System.h"
#include "Platform/Graphics/VertexBuffer.h"
#include "Platform/Graphics/Shader.h"

namespace EM {

	class Graphic : public System
	{
	public:

		//For Debugging Purposes
		virtual std::string GetName() { return "graphic"; }

		virtual void Init() override;
		virtual void Update() override;
		virtual void End() override;
	private:
		//for testing
		//unsigned int m_VertexArray{ 0 };
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexBuffer> m_Vbuffer;
		std::shared_ptr<IndexBuffer> m_Ibuffer;
		std::shared_ptr<VertexArray> m_vertexArr;

		struct obj {
			glm::vec2 position{ 0.0f, 0.0f };
			float dir{ 0.0f };
			glm::vec2 scale{ 0.0f, 0.0f };
		}player, wall;
	};
}