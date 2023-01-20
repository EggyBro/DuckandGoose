/*!*************************************************************************
****
\file			Texture.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			09-28-2022
\brief			This file contain the neccesary declaration functions for class texture.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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

		inline unsigned int GetWidth() const { return mWidth; }
		/*void SetWidth(unsigned int width) { mWidth *= width; }*/
		inline unsigned int GetHeight() const { return mHeight; }
		inline unsigned int GetRendererID() const { return mRendererID; }

		bool operator==(const Texture& other) const
		{
			return mRendererID == other.GetRendererID();
		}
		void setInternalFormat(unsigned int interformat) { mInnerFormat = interformat; }
		void setImageFormat(unsigned int imageformat) { mImageFormat = imageformat; }
	private:
		unsigned int mRendererID = 0;		//ID of the texture object
		unsigned int mWidth, mHeight;	//width and height of the loaded image in pixels
		unsigned int mWrapS, mWrapT;	// wrapping mode on S and T axis
		unsigned int mFilterMin, mFilterMax; // filtering mode if texture pixels > or < screen pixels( 1648 by 720 )
		unsigned int mInnerFormat, mImageFormat;
	};
}