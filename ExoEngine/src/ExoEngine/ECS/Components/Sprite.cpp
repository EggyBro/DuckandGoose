#include "empch.h"
#include "Sprite.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	Sprite::Sprite() : m_texturename("Blank"), m_index({0.0f,0.0f})
	{
	}
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{
		m_texturename = std::string(obj["TextureName"].GetString());
		m_index = vec2D(obj["Index_X"].GetFloat(), obj["Index_Y"].GetFloat());
		return true;
	}
	bool Sprite::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("TextureName");
		writer->String(m_texturename.c_str());
		writer->Key("Index_X");
		writer->Double(m_index.x);
		writer->Key("Index_Y");
		writer->Double(m_index.y);
		writer->EndObject();
		return true;
	}
	
	
}