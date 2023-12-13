#pragma once
#include "../../core/headers/Layer.h"
#include "../../Events/Events.h"
#include "../../GUI/include/Screen.h"
namespace Lina { namespace Layer{
    class GUI : public Core::Layer
    {
        public:
            GUI() {}
            ~GUI() = default;

            virtual void onAttach() override;
            virtual void onDetach() override;
            virtual void onEvent(Events::Event& e) override;
            //virtual std::vector<Events::Event> getEvents() override;

            void begin();
            void end();

            void setDarkTheme();
        private:
            //std::vector<Lina::GUI::Screen*> mScreens;
            //std::vector<Events::Event> screenEvents;
    };
}}
