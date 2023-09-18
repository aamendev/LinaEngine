#pragma once
#include "../Events/Events.h"
namespace Lina {
    class Layer
    {
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate() {}
        virtual void onEvent(Event& e) {}

    };

}
