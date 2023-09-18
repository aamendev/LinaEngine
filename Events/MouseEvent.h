#pragma once
#include "KeyCodes.h"
#include "Event.h"
#include <sstream>
namespace Lina{ namespace Events{

    class MouseMoved : public Event
    {
        MouseMoved(const float x, const float y): mX(x), mY(y){}
        float getX() const { return mX; }
        float getY() const { return mY; }

        std::string streamDetails() const override
        {
            std::stringstream ss;
            ss << "MouseMoved: (" << mX << ", "<< mY<<")";
            return ss.str();
        }

        EVENT_TYPE(MouseMoved);
        EVENT_CATEGORY(Category::Mouse | Category::Input);
        private:
            float mX, mY;
    };
    class MouseScrolled : public Event
    {
        MouseScrolled(const float x, const float y): mX(x), mY(y){}
        float getX() const { return mX; }
        float getY() const { return mY; }

        std::string streamDetails() const override
        {
            std::stringstream ss;
            ss << "MouseScrolled: (" << mX << ", "<< mY<<")";
            return ss.str();
        }

        EVENT_TYPE(MouseScrolled);
        EVENT_CATEGORY(Category::Mouse | Category::Input);
        private:
            float mX, mY;
    };

    class MouseButton : public Event
    {
        public:
            MouseCode getButton() const {return mButton;}
            EVENT_CATEGORY(Category::Mouse | Category::Input | Category::MouseButton);
        protected:
            MouseButton(const MouseCode button) : mButton(button){}
            MouseCode mButton;
    };

    class MouseButtonPressed : public MouseButton
    {
        public:
            MouseButtonPressed(const MouseCode button) : MouseButton(button) {}

        std::string streamDetails() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressed: (" << mButton<<")";
            return ss.str();
        }
        EVENT_TYPE(MousePressed);
    };

    class MouseButtonReleased : public MouseButton
    {
        public:
            MouseButtonReleased(const MouseCode button) : MouseButton(button) {}

        std::string streamDetails() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleased: (" << mButton<<")";
            return ss.str();
        }
        EVENT_TYPE(MouseReleased);
    };

}}
