#include "evpch.h"
#include "LayerStack.h"

namespace Envii
{
	Envii::LayerStack::LayerStack()
	{
	}

	Envii::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Envii::LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
		m_InsertIndex++;
	}

	void Envii::LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
			m_InsertIndex--;
		}
	}

	void Envii::LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void Envii::LayerStack::PopOverlay(Layer* overlay)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
		}
	}
}

