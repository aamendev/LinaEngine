#pragma once
#include "Layer.h"

namespace Lina{ namespace Core{
    class LayerStack
    {
        public:
            LayerStack() = default;

            void pushLayer(Layer& layer);
            void pushOverlay(Layer& layer);
            void popLayer(Layer& layer);
            void popOverlay(Layer& layer);

            std::vector<Layer&>::iterator begin() { return mLayers.begin(); }
            std::vector<Layer&>::iterator end() { return mLayers.end(); }
            std::vector<Layer&>::reverse_iterator rbegin() { return mLayers.rbegin(); }
            std::vector<Layer&>::reverse_iterator rend() { return mLayers.rend(); }

            std::vector<Layer&>::const_iterator begin() const { return mLayers.begin(); }
            std::vector<Layer&>::const_iterator end()	const { return mLayers.end(); }
            std::vector<Layer&>::const_reverse_iterator rbegin() const { return mLayers.rbegin(); }
            std::vector<Layer&>::const_reverse_iterator rend() const { return mLayers.rend(); }
        private:
            std::vector<Layer&> mLayers;
    };
}}
