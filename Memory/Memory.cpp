#include "include/Memory.h"
namespace Lina{ namespace Manager{
    static MemoryStats stats;

    void Memory::Init()
    {
    }
    MemoryStats Memory::Shutdown()
    {
        return stats;
    }

    void* Memory::lalloc(u64 size, MemoryCategory cat)
    {
        if (cat == UNKNOWN)
            std::cout<<"Change this asap!\n";
        stats.totalAllocations += size;
        stats.perCategoryAllocations[cat] += size;
        return malloc(size);
    }
    void Memory::lfree(void* block, u64 size)
    {
        if (!block)
            return;
        stats.totalFrees += size;
        free(block);
    }
    void* Memory::lzero(void* block, u64 size)
    {
        return memset(block, 0, size);
    }
    void* Memory::lset(void* block, i32 value, u64 size)
    {
        return memset(block, value, size);
    }
    void* Memory::lcopy(void* dest, const void* source, u64 size)
    {
       return memcpy(dest, source, size);
    }
    std::ostream& operator<<(std::ostream& os, MemoryStats& stats)
    {
        os << "Total Allocation: "<< stats.totalAllocations<< "\nTotal Frees: "
            << stats.totalFrees << "\nLeaks: " << stats.currentUsage() <<
            "\n Per Category Allocations {\n";
        for (u64 i = 0; i < sizeof(stats.perCategoryAllocations) / sizeof(u64); i++)
            os << "\tCategory " << i << ": " << stats.perCategoryAllocations[i]<<";\n";
        os << "}";
        return os;
    }
}}
