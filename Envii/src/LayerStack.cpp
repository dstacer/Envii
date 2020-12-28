#include "evpch.h"
#include "LayerStack.h"

namespace Envii
{
	Envii::LayerStack::LayerStack()
	{
		m_Inserter = m_Layers.begin();
	}

	Envii::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void Envii::LayerStack::PushLayer(Layer* layer)
	{
		m_Inserter = m_Layers.emplace(m_Inserter, layer);
	}

	void Envii::LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (iter != m_Layers.end())
		{
			m_Layers.erase(iter);
			m_Inserter--;
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

