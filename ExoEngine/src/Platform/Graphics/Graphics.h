#pragma once
#include "Platform/Window/Window.h"
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
		unsigned int m_VertexArray{ 0 }, m_VertexBuffer{ 0 }, m_IndexBuffer{ 0 };
		std::unique_ptr<Shader> m_shader;
	};
}