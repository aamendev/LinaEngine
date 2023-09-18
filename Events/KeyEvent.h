#pragma once

#include "Event.h"
#include "KeyCodes.h"
#include <sstream>

namespace Lina{ namespace Events{
    class KeyEvent: public Event
    {
        public:
            KeyCode getKeyCode() const {return mKeyCode;}

            EVENT_CATEGORY(Category::Keyboard | Category::Input);
        protected:
            KeyEvent(const KeyCode keycode): mKeyCode(keycode){}
            KeyCode mKeyCode;
    };

    class KeyPressed : public KeyEvent
    {
        public:
            KeyPressed(const KeyCode keycode, bool isRepeat = false)
                : KeyEvent(keycode), mIsRepeat(isRepeat){}
            bool isRepeated() {return mIsRepeat;}
            std::string streamDetails() const override
            {
                std::stringstream ss;
                ss << "(Key: " << mKeyCode << ", Repeated: " << mIsRepeat << ")";
                return ss.str();
            }

            EVENT_TYPE(KeyPressed);
        private:
            bool mIsRepeat;
    };

    class KeyReleased : public KeyEvent
    {
        public:
            KeyReleased(const KeyCode keycode)
                : KeyEvent(keycode){}

            std::string streamDetails() const override
            {
                std::stringstream ss;
                ss << "(Key: " << mKeyCode << ")";
                return ss.str();
            }

            EVENT_TYPE(KeyReleased);
    };

    class KeyTyped : public KeyEvent
    {
        public:
            KeyTyped(const KeyCode keycode)
                : KeyEvent(keycode){}

            std::string streamDetails() const override
            {
                std::stringstream ss;
                ss << "(Key: " << mKeyCode << ")";
                return ss.str();
            }

            EVENT_TYPE(KeyTyped);
    };
}}
