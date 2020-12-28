#pragma once

#include <string>
#include "Events/Event.h"

namespace Envii
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_Name; }

	protected:
		// TODO: Only store name in debug builds 
		std::string m_Name;
	};
}