#pragma once

#include <functional>
#include <string>
namespace Lina{ namespace Events{
    enum class Type
    {
        None = 0,
        WindowClose, WindowResize, WindoFocus, WindowMove,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MousePressed, MouseReleased, MouseMoved, MouseScrolled,
        RenderSpawn
    };
    enum Category
    {
        None = 0,
        Application = 1 << 0,
        Input =  1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 3,
        MouseButton = 1 << 4,
        Window = 1 << 5,
        Render = 1 << 6
    };
#define EVENT_TYPE(type) static Type getStaticType() { return Type::type;}\
                        virtual Type getType() const override {return getStaticType();}\
                        virtual std::string getName() const override {return #type;}
#define EVENT_CATEGORY(cat) virtual int getCategory() const override {return cat;}
    class Event
    {
        public:
            virtual ~Event() = default;
            bool handled = false;

            virtual Type getType() const = 0;
            virtual std::string getName() const = 0;
            virtual int getCategory() const = 0;
            virtual std::string streamDetails() const {}

            bool isInCategory(Category cat)
            {
                return getCategory() & cat;
            }
    };
    class Dispatcher
    {
        public:
            Dispatcher(Event& e): mEvent(e){}

            template<typename eventType, typename eventFunction>
            bool dispatch(const eventFunction& func)
            {
                if (mEvent.getType() == eventType::getStaticType())
                {
                    mEvent.handled |= func(static_cast<eventType&>(mEvent));
                    return true;
                }
                return false;
            }
        private:
            Event& mEvent;
    };
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.getName();
    }
}}
