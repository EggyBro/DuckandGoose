/*!*************************************************************************
****
\file			ResourceManager.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	CSD2400 / GAM200
\date			11-2-2022
\brief			This file contain the defintion for ResourceManager class.
				
****************************************************************************
***/
#pragma once
#include "Platform/Graphics/Texture.h"
#include "Platform/Graphics/Shader.h"
#include "Platform/Graphics/TextRendering.h"
#include "ExoEngine/Audio/AudioEngine.h"

namespace EM {

	class ResourceManager
	{
	public:
		static std::map<std::string, std::shared_ptr<Texture>> textures;
		static std::map<std::string, std::shared_ptr<Shader>> shaders;
		static std::map<std::string, std::shared_ptr<Font>> fonts;
		static std::map<std::string, std::shared_ptr<CAudioEngine>> audios;
		static std::map<std::string, std::shared_ptr<Texture>> Icons;
	public:
		//load texture from file
		static std::shared_ptr<Texture> LoadTexture(std::string name, const std::string& filepath);
		static std::shared_ptr<Texture> GetTexture(std::string name);
		static std::shared_ptr<Texture> GenTexture(unsigned int width, unsigned int height);
		
		// load Icon texture from file to differentiate the sprite, background and icons texture
		static std::shared_ptr<Texture> LoadIcons(std::string name, const std::string& filepath);
		static std::shared_ptr<Texture> GetIcon(std::string name);

		//load shader from file
		static std::shared_ptr<Shader> LoadShader(std::string name, const std::string& filepath);
		static std::shared_ptr<Shader> GetShader(std::string name);
		
		static std::shared_ptr<CAudioEngine> GetAudio(std::string name);
		static std::shared_ptr<CAudioEngine> LoadAudio(std::string name, const std::string& filepath);
		
		////load different type of fonts from file tff
		//static std::shared_ptr<Font> LoadFont(std::string name, unsigned int size);
		//static std::shared_ptr<Font> GetFont(std::string name);
		static void clear();
	private:
		
	private:
		// private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
		ResourceManager() {}
		static std::shared_ptr<CAudioEngine> LoadAudioFromFile(const std::string& filepath);
		
		//loads texture
		static std::shared_ptr<Texture> LoadTextureFromFile(const std::string& filepath);

		// generates shader from file
		static std::shared_ptr<Shader> LoadShaderFromFile(const std::string& filepath);

		// generates font from file
		static std::shared_ptr<Font> LoadFontFromFile(const std::string& filepath, unsigned int fontsize);

		//loads Icons texture
		static std::shared_ptr<Texture> LoadIconsFromFile(const std::string& filepath);
	};
}