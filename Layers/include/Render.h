#pragma once
#include "../../core/headers/Layer.h"
#include "../../Events/Events.h"
#include "../../Graphics/Renderer.h"
namespace Lina{ namespace Layer{
    class Render : Core::Layer
    {
        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onEvent(Events::Event& e) override;
        virtual void onUpdate(Core::TimeStep t) override;
    };
}}
