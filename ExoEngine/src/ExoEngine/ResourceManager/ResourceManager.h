#pragma once
#include "Platform/Graphics/Texture.h"
#include "Platform/Graphics/Shader.h"
#include "Platform/Graphics/TextRendering.h"

namespace EM {

	class ResourceManager
	{
	public:
		static std::map<std::string, std::shared_ptr<Texture>> textures;
		static std::map<std::string, std::shared_ptr<Shader>> shaders;
		static std::map<std::string, std::shared_ptr<Font>> fonts;
	public:
		//load texture from file
		static std::shared_ptr<Texture> LoadTexture(std::string name, const std::string& filepath);
		static std::shared_ptr<Texture> GetTexture(std::string& name);
		static std::shared_ptr<Texture> GenTexture(unsigned int width, unsigned int height);
		//load shader from file
		static std::shared_ptr<Shader> LoadShader(std::string name, const std::string& filepath);
		static std::shared_ptr<Shader> GetShader(std::string name);

		////load different type of fonts from file tff
		//static std::shared_ptr<Font> LoadFont(std::string name, unsigned int size);
		//static std::shared_ptr<Font> GetFont(std::string name);
		static void clear();
	private:
		
	private:
		// private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
		ResourceManager() {}

		//loads texture
		static std::shared_ptr<Texture> LoadTextureFromFile(const std::string& filepath);

		// generates shader from file
		static std::shared_ptr<Shader> LoadShaderFromFile(const std::string& filepath);

		// generates font from file
		static std::shared_ptr<Font> LoadFontFromFile(const std::string& filepath, unsigned int fontsize);
	};
}