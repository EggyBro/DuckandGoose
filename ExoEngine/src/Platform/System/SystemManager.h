#pragma once
#include "ExoEngine/Core.h"
#include "Platform/System/System.h"

namespace EM {

	class SystemManager
	{
	public:
		SystemManager() = default;
		~SystemManager();

		void SystemIncrement(System* system);
		void SystemIndex(unsigned int index, System* system);
		//Destroy Systems
		void DeleteSystem();

	public:
		//Iterating the gameloop
		std::vector<System*>::iterator start() { return m_Systems.begin(); };
		std::vector<System*>::iterator end() { return m_Systems.end(); }
	private:
		std::vector<System*> m_Systems;
	};
}