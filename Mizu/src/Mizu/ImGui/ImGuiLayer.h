#pragma once

#include "Mizu/Core/Layer.h"

#include "Mizu/Events/ApplicationEvent.h"
#include "Mizu/Events/KeyEvent.h"
#include "Mizu/Events/MouseEvent.h"

namespace Mizu {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Being();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
