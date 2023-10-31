#pragma once
#include "../../Types.h"

namespace Lina { namespace Core{
    class TimeStep
    {
        public:
            TimeStep(f32 time = 0.0f): mTime(time) {}
            f32 getSeconds() { return mTime; }
            f32 getMilliSeconsd() { return mTime * 1000.0f; }
        private:
            f32 mTime;
    };
}}
