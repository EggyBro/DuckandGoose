/*!*************************************************************************
****
\file			SpriteRendering.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-02-2022
\brief			This file do rendering for sprite
****************************************************************************
***/
#include "empch.h"
#include "SpriteRendering.h"

namespace EM {

	/*!*************************************************************************
	Render sprite using glm
	****************************************************************************/
	SpriteRender::SpriteRender(const MultiRefs<Texture>& texture, const glm::vec2& min, const glm::vec2& max)
		:m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y }; //bottom left
		m_TexCoords[1] = { max.x, min.y }; //bottom right
		m_TexCoords[2] = { max.x, max.y }; //top right
		m_TexCoords[3] = { min.x, max.y }; //top left
	}

	/*!*************************************************************************
	Create sprite using glm
	****************************************************************************/
	MultiRefs<SpriteRender> SpriteRender::CreateSprite(const MultiRefs<Texture>& texture, const glm::vec2& Coordinates, const glm::vec2& SpriteSize)
	{
		glm::vec2 min = { (Coordinates.x * SpriteSize.x) / texture->GetWidth(), (Coordinates.y * SpriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((Coordinates.x + 1) * SpriteSize.x) / texture->GetWidth(), ((Coordinates.y + 1) * SpriteSize.y) / texture->GetHeight() };
		
		return CreateMultiRefs<SpriteRender>(texture, min, max);
	}
}
