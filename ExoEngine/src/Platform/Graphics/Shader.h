/*!*************************************************************************
****
\file			Shader.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain function declaration for Shader classes

****************************************************************************
***/
#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
namespace EM {

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//function overload 
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, int* value, unsigned int count);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetUniform(const std::string& name, const glm::vec4& value);
		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> Processing(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:

		unsigned int m_RendererID;
		std::string m_Name;
	};
}