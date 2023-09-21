#pragma once

namespace Lina { namespace Core{
    class TimeStep
    {
        public:
            TimeStep(float time = 0.0f): mTime(time) {}
            float getSeconds() { return mTime; }
            float getMilliSeconsd() { return mTime * 1000.0f; }
        private:
            float mTime;
    };
}}
