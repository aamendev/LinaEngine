namespace Lina{ namespace Events{
    class Listener
    {
        public:
            virtual void onEvent(Event& e) = 0;
    }
}}
