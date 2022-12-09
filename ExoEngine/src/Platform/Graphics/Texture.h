/*!*************************************************************************
****
\file			Texture.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			09-28-2022
\brief			This file contain the neccesary declaration functions for class texture.

****************************************************************************
***/

#pragma once

namespace EM {

	class Texture
	{
	public:
		Texture();
		~Texture();
		void Bind(unsigned int slot = 0) const; //  specify the slot to bind texture to
		void UnBind() const;
		void GenTexture(const std::string& path);
		void GenTexture(unsigned int width, unsigned int height);
		/* accessor functions for the width, height, bpp */

		void SetTextureData(void* data, unsigned int size);

		inline unsigned int GetWidth() const { return _width; }
		/*void SetWidth(unsigned int width) { _width *= width; }*/
		inline unsigned int GetHeight() const { return _height; }
		inline unsigned int GetRendererID() const { return m_RendererID; }

		bool operator==(const Texture& other) const
		{
			return m_RendererID == other.GetRendererID();
		}
		void setInternalFormat(unsigned int interformat) { inner_format = interformat; }
		void setImageFormat(unsigned int imageformat) { image_format = imageformat; }
	private:
		unsigned int m_RendererID = 0;		//ID of the texture object
		unsigned int _width, _height;	//width and height of the loaded image in pixels
		unsigned int _wrapS, _wrapT;	// wrapping mode on S and T axis
		unsigned int _FilterMin, _FilterMax; // filtering mode if texture pixels > or < screen pixels( 1648 by 720 )
		unsigned int inner_format, image_format;
	};
}