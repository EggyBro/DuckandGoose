/*!*************************************************************************
****
\file SystemManager.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains a general implementation of a System Manager in
place of the ECS. It stores a vector of systems registered during runtime
****************************************************************************
***/

#include "empch.h"
#include "SystemManager.h"
namespace EM {

	SystemManager::~SystemManager()
	{
	}

	void SystemManager::SystemIncrement(System* system)
	{
		m_Systems.emplace_back(system);
	}

	void SystemManager::SystemIndex(unsigned int index, System* system)
	{
		m_Systems.insert(index + m_Systems.begin(), system);
	}

	void SystemManager::DeleteSystem()
	{
		for (System* system : m_Systems)
		{
			std::cout << system->GetName() << std::endl;
			system->End();
			delete system;
		}
	}
}