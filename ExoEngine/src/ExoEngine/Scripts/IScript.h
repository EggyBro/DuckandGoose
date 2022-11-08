#pragma once
#include "ExoEngine/ECS/Types.h"
#include "ExoEngine/ECS/ECS.h"

namespace EM
{
	class IScript
	{
	public:
		virtual ~IScript() = default;
		virtual void Start() {};
		virtual void Update(float Frametime) { UNREFERENCED_PARAMETER(Frametime); };
		virtual void End() {};
		virtual IScript* Clone() const = 0;

		//template<typename T>
		//T& GetComponent(Entity entity) 
		//{
		//	p_ecs.GetComponent<T>(entity);
		//};
		void SetEntityID(Entity entity) { entityID = entity; }
		Entity GetEntityID() { return entityID; }
	private:
		Entity entityID;
	};
}