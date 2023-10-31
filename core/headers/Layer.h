#pragma once
#include "../../Events/Events.h"
#include "TimeStep.h"
namespace Lina { namespace Core{
    class Layer
    {
        public:
        virtual ~Layer() {};

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(TimeStep ts) {}
        virtual void onGUIRender() {}
        virtual void onEvent(Events::Event& e) {}
    };

}}
