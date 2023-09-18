#include "../LayerStack.h"

namespace Lina { namespace Core{
    LayerStack::pushLayer(Layer& layer)
    {
        mLayers.emplace_back(layer);
    }
}}
