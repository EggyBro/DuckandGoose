#pragma once
#include "Serialization/JSONserialization.h"
#include "empch.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/ECS/Types.h"

namespace EM
{
	//When Buiilding a New Component
	//Ensure that the SceneManager Init has the component registered
	//Ensure that the Serialize and De-Serialize functions in the SceneManager has those components checked
	class IComponent : public JSONSerializer
	{
	public:
		virtual ~IComponent() = default;
		virtual void ToEditor() {}
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;
		Entity entityID;
	//protected:
	};
}