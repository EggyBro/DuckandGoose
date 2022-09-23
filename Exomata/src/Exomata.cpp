#include "ExoEngine.h"
#include "ExoEngine/EntryPoint.h"

class Exomata : public EM::Application
{
public:
	Exomata() 
	{

	}
	~Exomata() 
	{

	}
};

EM::Application* EM::CreateApplication()
{
	return new Exomata();
}
