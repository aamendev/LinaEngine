#pragma once
#include "../../core/headers/Layer.h"
#include "../../Events/Events.h"
namespace Lina { namespace Layer{
    class GUI : public Core::Layer
    {
        public:
            GUI() {}
            ~GUI() = default;

            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual void onEvent(Events::Event& e) override;

            void begin();
            void end();

            void setDarkTheme();
    };
}}
