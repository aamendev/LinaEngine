#pragma once

#include "Event.h"
#include <sstream>
namespace Lina { namespace Events{
    class WindowResize : public Event
    {
        public:
            WindowResize(unsigned int width, unsigned int height)
                            : mWidth(width), mHeight(height) {}
            unsigned int getWidth() { return mWidth; }
            unsigned int getHeight() { return mHeight; }

            std::string streamDetails() const override
            {
                std::stringstream ss;
                ss << "WindowResize: ("<< mWidth << ", " << mHeight << ")";
                return ss.str();
            }

            EVENT_TYPE(WindowResize);
            EVENT_CATEGORY(Category::Window);
        private:
            unsigned int mWidth, mHeight;
    };

    class WindowClose : public Event
    {
        public:
            WindowClose() = default;

            EVENT_TYPE(WindowClose);
            EVENT_CATEGORY(Category::Window);
    };
}}
