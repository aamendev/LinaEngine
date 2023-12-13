#pragma once
#include <vector>
#include "../../core/headers/Layer.h"
#include "../../Types.h"
#include "../../Events/Event.h"
#include "../../Layers/include/GUI.h"
namespace Lina{ namespace Manager{
    class Layer
    {
        public:
            Layer() = default;
            b8 init();
            void spreadEvent(Events::Event& event);
            void addLayer(Core::Layer* layer);
            b8 popLayer();
            void handleEvents();
        private:
            std::vector<Core::Layer*> mLayers;
            Lina::Layer::GUI* mGuiLayer;

    };
}}
