#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"
#include "Platform/Graphics/Texture.h"
namespace EM {

	class Sprite : public IComponent
	{
	public:
		Sprite();
		~Sprite() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		void SetTexture(const std::string& name) { m_texturename = name; }
		std::string &GetTexture() { return m_texturename; }

		void SetIndex(float& x) { m_index.x = x; }
		vec2D& GetIndex() { return m_index; }
		//boolean isanimated
		//altas 
	private:
		std::string m_texturename;
		vec2D m_index;
	};
}