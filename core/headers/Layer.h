#pragma once
#include "../../Events/EventListener.h"
#include "../../Events/Events.h"
#include "TimeStep.h"
#include <vector>
namespace Lina { namespace Core{
    class Layer : public Events::IListener
    {
        public:
        virtual ~Layer() {};

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(TimeStep ts) {}
        virtual void onGUIRender() {}
        virtual void onEvent(Events::Event& e) {}
        //virtual std::vector<Events::Event> getEvents() = 0;
    };

}}
