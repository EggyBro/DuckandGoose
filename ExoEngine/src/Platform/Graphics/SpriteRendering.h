/*!*************************************************************************
****
\file			SpriteRendering.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-02-2022
\brief			This file header contain all the necessary declaration for
				SpriteRendering

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

namespace EM {

	class SpriteRender
	{
	public:
		SpriteRender(const MultiRefs<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

		const MultiRefs<Texture> GetTexture()const { return mTexture; }// retrive Texture	
		const glm::vec2* GetTexCoords()const { return mTexCoords; }	// retrieve texture coordinates

		//helper function to spilt the spritesheet 
		static MultiRefs<SpriteRender> CreateSprite(const MultiRefs<Texture>& texture, const glm::vec2& Coordinates, const glm::vec2& SpriteSize = { 512.0f, 512.0f});// our sprite sheet is standard 512 by 512

		
	private:
		MultiRefs<Texture> mTexture;
		glm::vec2 mTexCoords[4];
	};
}