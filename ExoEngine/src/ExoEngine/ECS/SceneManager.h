#pragma once

#include "ECS.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "Platform/System/SystemManager.h"
#include "Types.h"
#include "empch.h"
#include "Serialization/JSONserialization.h"
#include "Serialization/JSONincludes.h"

#define p_Scene EM::SceneManager::GetInstance()

namespace EM
{

	class SceneManager : public JSONSerializer
	{
	public:

		static std::unique_ptr<SceneManager>& GetInstance();

		void Init();
		Entity GetEntities()
		{
			return p_ecs.GetTotalEntities();
		}

		virtual bool Deserialize(const rapidjson::Value& obj);

		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
		
	private:
		static std::unique_ptr<SceneManager> m_instance;
	};
}