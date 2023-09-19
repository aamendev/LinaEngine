#include "../headers/LayerStack.h"

namespace Lina { namespace Core{
    LayerStack::pushLayer(Layer& layer)
    {
        mLayers.emplace_back(layer);
    }
    LayerStack::popLayer()
    {
        mLayers.pop_back();
    }
}}
