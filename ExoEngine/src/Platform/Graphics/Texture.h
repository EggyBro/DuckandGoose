/*!*************************************************************************
****
\file			Texture.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
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
		/* accessor functions for the width, height, bpp */

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }
		inline int GetRendererID() const { return m_RendererID; }

		void setInternalFormat(unsigned int interformat) { inner_format = interformat; }
		void setImageFormat(unsigned int imageformat) { image_format = imageformat; }

	private:
		unsigned int m_RendererID = 0;		//ID of the texture object
		unsigned int _width, _height;	//width and height of the loaded image in pixels
		unsigned int _wrapS, _wrapT;	// wrapping mode on S and T axis
		unsigned int _FilterMin, _FilterMax; // filtering mode if texture pixels > or < screen pixels( 1648 by 720 )
		unsigned int inner_format, image_format;// format of texture object and loaded image
	};
}