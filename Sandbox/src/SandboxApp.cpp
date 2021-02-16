#include <DAGGer.h>
// Entry Point
#include <DAGGer/Core/Entry.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public DAGGer::Application
{
public:
	Sandbox()
		: Application("DAGGer Application")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};	//	END class Sandbox

DAGGer::Application* DAGGer::CreateApplication()
{
	return new Sandbox();
}	//	END CreateApplication