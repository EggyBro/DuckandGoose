/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-11-2022
\brief			This file sets frame data for animations

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Animation.h"


namespace EM {
	std::unordered_map<std::string, std::vector<float>> Animation::spriteContainer;
	/*!*************************************************************************
	Constructor for animation
	****************************************************************************/
	Animation::Animation()
	{

	}

	/*!*************************************************************************
	Update animations based on delta time
	****************************************************************************/
	void Animation::UpdateAnimation(float deltatime, Sprite& sprite)
	{
		sprite.internaltimer += deltatime;
	
		std::unordered_map <std::string, std::vector <float>> ::const_iterator got = spriteContainer.find(sprite.GetTexture());
		if (got == spriteContainer.end())// always check the sprite container whether there is any data for the current texture. if no, prompt the user
		{
			//std::cout << sprite.GetTexture() << " not in  the container" << std::endl;
		}
		else
		{
			sprite.GetMaxIndex() = static_cast<int>(GETTEXTURE(sprite.GetTexture())->GetWidth() / 512.f);
			if (sprite.internaltimer >= spriteContainer[sprite.GetTexture()][sprite.GetIndex().x])
			{
				////for debug
				//if(sprite.GetTexture() == "Attack")
				//	std::cout <<"Att " << sprite.GetIndex().x << ":  " << spriteContainer[sprite.GetTexture()][sprite.GetIndex().x] << std::endl;
				//
				//if (sprite.GetTexture() == "Idle")
				//	std::cout << "Idle " << sprite.GetIndex().x << ":  " << spriteContainer[sprite.GetTexture()][sprite.GetIndex().x] << std::endl;

				//if (sprite.GetTexture() == "Running")
				//	std::cout << "Running " << sprite.GetIndex().x << ":  " << spriteContainer[sprite.GetTexture()][sprite.GetIndex().x] << std::endl;
				//
				//end of debug
				sprite.GetIndex().x++;
				sprite.internaltimer = 0.0f;
				if (sprite.GetIndex().x >= sprite.GetMaxIndex())
				{
					sprite.GetIndex().x = 0;
				}
			}
		}
	}

}