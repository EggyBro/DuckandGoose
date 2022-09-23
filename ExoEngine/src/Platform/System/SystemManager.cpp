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