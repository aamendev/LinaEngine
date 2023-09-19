#pragma once

namespace Lina { namespace Core{
    class TimeStep
    {
        public:
            TimeStep(float time = 0.0f): mTime(time) {}
            float getSeconds { returm mTime; }
            float getMilliSeconsd { returm mTime * 1000.0f; }
        private:
            float mTime;
    };
}}
