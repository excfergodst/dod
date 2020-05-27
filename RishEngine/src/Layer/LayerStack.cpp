#include "Rish/Layer/LayerStack.h"

namespace rl {

LayerStack::LayerStack()
{
	m_LayerInsert = begin();
}

LayerStack::~LayerStack()
{
	for(Layer* layer: m_Layers) delete layer;
}

void LayerStack::pushLayer(Layer* layer)
{
	m_Layers.emplace(m_LayerInsert, layer);
	m_LayerInsert++;
}

void LayerStack::pushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer)
{
	auto it = std::find(begin(), end(), layer);
	if(it != end())
	{
		m_Layers.erase(it);
		m_LayerInsert--;
	}
}

void LayerStack::popOverlay(Layer* layer)
{
	auto it = std::find(begin(), end(), layer);
	if(it != end()) m_Layers.erase(it);
}


}
