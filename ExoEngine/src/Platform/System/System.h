#pragma once

#include "ExoEngine/Core.h"

namespace EM {

	class EM_API System
	{
	public:
		
		virtual std::string GetName() = 0;
		virtual ~System() {};
		//System function
		virtual void Init() = 0 {};
		virtual void Update() = 0 {};
		virtual void End() = 0 {};
		
	protected:
		std::string m_DebugName;

	};
}