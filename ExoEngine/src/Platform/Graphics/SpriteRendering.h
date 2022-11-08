#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

namespace EM {

	class SpriteRender
	{
	public:
		SpriteRender(const MultiRefs<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

		const MultiRefs<Texture> GetTexture()const { return m_Texture; }// retrive Texture	
		const glm::vec2* GetTexCoords()const { return m_TexCoords; }	// retrieve texture coordinates

		//helper function to spilt the spritesheet 
		static MultiRefs<SpriteRender> CreateSprite(const MultiRefs<Texture>& texture, const glm::vec2& Coordinates, const glm::vec2& SpriteSize = { 512.0f, 512.0f});// our sprite sheet is standard 512 by 512

		
	private:
		MultiRefs<Texture> m_Texture;
		glm::vec2 m_TexCoords[4];
	};
}