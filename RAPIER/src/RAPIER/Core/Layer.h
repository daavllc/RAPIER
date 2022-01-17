#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/Timestep.h"
#include "RAPIER/Core/Events/Event.h"

namespace RAPIER
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}	//	END namespace RAPIER