#pragma once
#include <iostream>
namespace Lina { namespace Memory{
    struct AllocationMetrics
    {
        uint32_t TotalAllocation = 0;
        uint32_t TotalReleased = 0;
        uint32_t Usage() { return TotalAllocation - TotalReleased;}
    };

   /* std::ostream& operator<<(std::ostream& os, AllocationMetrics& metrics)
    {
        os<< "TotalAllocs: " << metrics.TotalAllocation
            <<"Total Releases: " << metrics.TotalReleased << "Currently Used: "
            << metrics.Usage();
        return os;
    }*/
}}
