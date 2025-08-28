#include <Mizu.h>
#include <Mizu/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Mizu::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

Mizu::Application* Mizu::CreateApplication()
{
	return new Sandbox();
}