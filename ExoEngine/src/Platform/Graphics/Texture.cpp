/*!*************************************************************************
****
\file			Texture.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the neccesary functions for loading the png and paste it on the window screen.

****************************************************************************
***/

#include "empch.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image/stb_image.h>
namespace EM {
	Texture::Texture()
		:_width {0}, _height{ 0 }, _wrapS{ GL_LINEAR }, _wrapT{ GL_LINEAR }, _FilterMin{ GL_CLAMP_TO_BORDER }, _FilterMax{ GL_CLAMP_TO_BORDER }, inner_format{ GL_RGB8 }, image_format{ GL_RGBA }
	{
	
	}

	Texture::~Texture()
	{

		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::GenTexture(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		_width = width;
		_height = height;
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		inner_format = internalFormat;
		image_format = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, _width, _height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}
}
