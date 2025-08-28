#pragma once

#include "Mizu/Core/Core.h"

#include "Mizu/Core/Window.h"
#include "Mizu/Core/LayerStack.h"
#include "Mizu/Events/Event.h"
#include "Mizu/Events/ApplicationEvent.h"

#include "Mizu/Core/Timestep.h"

#include "Mizu/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Mizu {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//Implement in client
	Application* CreateApplication();
}