/*!*************************************************************************
****
\file			Texture.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			09-28-2022
\brief			This file contain the neccesary functions for loading the png and paste it on the window screen.

****************************************************************************
***/

#include "empch.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stb_image/stb_image.h>
namespace EM {
	/*!*************************************************************************
	Constructor for texture
	****************************************************************************/
	Texture::Texture()
		:_width {0}, _height{ 0 }, _wrapS{ GL_LINEAR }, _wrapT{ GL_LINEAR }, _FilterMin{ GL_CLAMP_TO_BORDER }, _FilterMax{ GL_CLAMP_TO_BORDER }, inner_format{ GL_RGB8 }, image_format{ GL_RGBA }
	{
	}

	/*!*************************************************************************
	Destructor for texture
	****************************************************************************/
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	/*!*************************************************************************
	Bind texture 
	****************************************************************************/
	void Texture::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	/*!*************************************************************************
	Unbind texture
	****************************************************************************/
	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/*!*************************************************************************
	Generate texture from file
	****************************************************************************/
	void Texture::GenTexture(const std::string& path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = nullptr;
		{
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		if (data)
		{
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

			//EM_EXO_ASSERT(internalFormat && dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, inner_format, _width, _height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, _width, _height, image_format, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	/*!*************************************************************************
	Generate texture
	****************************************************************************/
	void Texture::GenTexture(unsigned int width, unsigned int height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, inner_format, width, height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	/*!*************************************************************************
	Set texture data
	****************************************************************************/
	void Texture::SetTextureData(void* data, unsigned int size)
	{
		uint32_t bpp = image_format == GL_RGBA ? 4 : 3;
		EM_EXO_ASSERT(size == _width * _height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, _width, _height, image_format, GL_UNSIGNED_BYTE, data);
	}
}
