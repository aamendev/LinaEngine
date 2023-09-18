#pragma once
#include "Events.h"
namespace Lina{ namespace Events{
        class AppTick : public Event
        {
            public:
                AppTick() = default;

                EVENT_TYPE(AppTick);
                EVENT_CATEGORY(Category::Application);
        };

        class AppUpdate : public Event
        {
            public:
                AppUpdate() = default;

                EVENT_TYPE(AppUpdate);
                EVENT_CATEGORY(Category::Application);
        };

        class AppRender : public Event
        {
            public:
                AppRender() = default;

                EVENT_TYPE(AppRender);
                EVENT_CATEGORY(Category::Application);
        };
}}
