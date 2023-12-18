#pragma once
#include "../../core/headers/Layer.h"
#include "../../Events/Events.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Icosphere.h"
#include "../../ECS/include/ECSManager.h"
#include "../../PlanetarySystem/Celestials/include/Planet.h"
namespace Lina{ namespace Layer{
    class Render : public Core::Layer
    {
        public:
            Render();
            ~Render() = default;
            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual void onEvent(Events::Event& e) override;
            virtual void onUpdate(Core::TimeStep t) override;
        private:
            std::pair<Manager::IndexedDrawingSpecifications,
                Manager::DrawData> mDrawing;
    };
}}
