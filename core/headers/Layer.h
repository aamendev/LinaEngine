#pragma once
#include "../../Events/Events.h"
#include "TimeStep.h"
namespace Lina { namespace Core{
    class Layer
    {
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(TimeStep ts) {}
        virtual void onEvent(Events::Event& e) {}
    };

}}
