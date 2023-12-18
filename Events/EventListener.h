#include "./Event.h"
namespace Lina{ namespace Events{
    class IListener
    {
        public:
            virtual ~IListener() {}
            virtual void onEvent(Event& e) = 0;
    };
}}
