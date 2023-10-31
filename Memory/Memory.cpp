#include "include/Memory.h"
namespace Lina{ namespace Manager{
    static MemorySpecs* specs;
    b8 Memory::Init(u64 totalSize)
    {
        u64 specsMemoryRequirement = sizeof(MemorySpecs);
        u64 allocMemoryRequirement = Allocation::Allocator::getMemoryRequirement(totalSize);
        void* block = new char[specsMemoryRequirement + allocMemoryRequirement];
        if (!block)
        {
            std::cout<<"Failed to Allocate\n";
            return false;
        }
        specs = reinterpret_cast<MemorySpecs*>(block);
        specs->sMemoryRequirement = allocMemoryRequirement;
        lzero(&specs->sStats, sizeof(specs->sStats));
        specs->sAllocatorBlock = ((b8*)block + specsMemoryRequirement);
        specs->sTotalSize = totalSize;
        if (!specs->sAllocator.Init(totalSize, specs->sAllocatorBlock))
        {
            std::cout<<"Failed to create Allocator\n";
            return false;
        }
        std::cout<<"Allocated "<< totalSize << " bytes\n";
        return true;
    }
    MemoryStats Memory::ShutDown()
    {
        MemoryStats s = specs->sStats;
        specs->sAllocator.Destroy();
        delete specs;
        specs = 0;
        return s;
    }

    void* Memory::lalloc(u64 size, MemoryCategory cat)
    {
        return lallocWithAlignment(size, cat, DEFAULT_ALIGNMENT);
    }
    void* Memory::lallocWithAlignment(u64 size, MemoryCategory cat, u16 alignment)
    {
        if (cat == UNKNOWN)
            std::cout<<"Change this asap!\n";
        specs->sStats.totalAllocations += size;
        specs->sStats.perCategoryAllocations[cat] += size;
        void* block = specs->sAllocator.allocateWithAlignment(size, alignment);
        if (!block)
        {
            std::cout<<"Error Allocating Memory with Allocator; Switching to malloc\n";
            block = malloc(size);
            return block;
        }
        if (block)
        {
            lzero(block, size);
            return block;
        }
        std::cout<<"Allocation Failed\n";
        return 0;
    }
    b8 Memory::lfree(void* block, u64 size)
    {
        if (!block)
        {
            std::cout<<"Invalid block!\n";
            return false;
        }
        if (specs)
        {
            if (!specs->sAllocator.freeWithAlignment(block))
            {
                std::cout<< "Failed to free from the Allocator; switching to system free\n";
                free(block);
            }
            else{
                specs-> sStats.totalFrees += size;
            }
        }
        else
        {
            free(block);
        }
        return true;
    }
    std::pair<u64, u16> Memory::getSizeAndAlignment(void* block)
    {
        return specs->sAllocator.getSizeAndAlignment(block);
    }
    u64 Memory::getSize(void* block)
    {
        return specs->sAllocator.getSize(block);
    }
    u16 Memory::getAlignment(void* block)
    {
        return specs->sAllocator.getAlignment(block);
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
    std::ostream& operator<<(std::ostream& os, MemoryStats&& stats)
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

