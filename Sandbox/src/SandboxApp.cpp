#include <RAPIER.h>
// Entry Point
#include <RAPIER/Core/Entry.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public RAPIER::Application
{
public:
	Sandbox()
		: Application("RAPIER Application")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};	//	END class Sandbox

RAPIER::Application* RAPIER::CreateApplication()
{
	return new Sandbox();
}	//	END CreateApplication