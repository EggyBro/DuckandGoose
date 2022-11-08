#include "empch.h"
#include "ResourceManager.h"


namespace EM {
	std::map <std::string, std::shared_ptr<Texture>> ResourceManager::textures;
	std::map <std::string, std::shared_ptr<Shader>> ResourceManager::shaders;
	//std::map <std::string, std::shared_ptr<Font>> ResourceManager::fonts;
	std::shared_ptr<Texture> ResourceManager::LoadTexture(std::string name, const std::string& filepath)
	{
		return textures[name] = ResourceManager::LoadTextureFromFile(filepath);
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(std::string& name)
	{
		return textures[name];
	}

	std::shared_ptr<Texture> ResourceManager::LoadTextureFromFile(const std::string& filepath)
	{
		auto m_texture = std::make_shared<Texture>();
		m_texture->GenTexture(filepath);
		return m_texture;
	}

	std::shared_ptr<Texture> ResourceManager::GenTexture(unsigned int width, unsigned int height)
	{
		auto m_texture = std::make_shared<Texture>();
		m_texture->GenTexture(width, height);
		return m_texture;
	}

	std::shared_ptr<Shader> ResourceManager::LoadShaderFromFile(const std::string& filepath)
	{
		auto m_shader = std::make_shared<Shader>(filepath);
		
		return m_shader;
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(std::string name, const std::string& filepath)
	{
		return shaders[name] = ResourceManager::LoadShaderFromFile(filepath);
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(std::string name)
	{
		return shaders[name];
	}

	std::shared_ptr<Font> ResourceManager::LoadFontFromFile(const std::string& filepath, unsigned int fontsize)
	{
		auto m_font = std::make_shared<Font>();
		m_font->Load(filepath, fontsize);
		return m_font;
	}

	//std::shared_ptr<Font> ResourceManager::LoadFont(std::string name, unsigned int size)
	//{
	//	return std::shared_ptr<Font>();
	//}

	//std::shared_ptr<Font> ResourceManager::GetFont(std::string name)
	//{
	//	return std::shared_ptr<Font>();
	//}

	void EM::ResourceManager::clear()
	{
		for (auto iter : textures)
			iter.second->~Texture();

		for (auto iter : shaders)
			iter.second->~Shader();
	}

	
}