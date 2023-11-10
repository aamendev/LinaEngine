#pragma once

#include "Event.h"
#include <sstream>
namespace Lina{ namespace Events{
    enum class Spawnable
    {
        Planet = 0, Star
    };
    class RenderEvent : public Event
    {
        public:
            EVENT_CATEGORY(Category::Render);
        protected:
            RenderEvent() = default;
    };

    class Spawn : public RenderEvent
    {
        public:
           Spawn(Spawnable s): mSpawnable(s) {};
           EVENT_TYPE(RenderSpawn);
           Spawnable getSpawnable() {return mSpawnable;}
        private:
          Spawnable mSpawnable;
    };
}}
