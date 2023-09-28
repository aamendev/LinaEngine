#include "include/Allocator.h"

namespace Lina{ namespace Memory{
    u64 Allocator::getMemoryRequirement(u64 size)
    {
        u64 freeListRequirement = FreeList::getMemoryRequirement(size);
        return freeListRequirement + sizeof(AllocatorSpecs) + size;
    }
    b8 Allocator::Init(u64 size)
    {
        if (size < 1)
            return false;
        mMemory = Manager::Memory::lalloc(Allocator::getMemoryRequirement(size));
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        specs->sTotalSize = size;
        specs->sFreeListBlock = (void*)((u8*)mMemory + sizeof(AllocatorSpecs));
        specs->sMemoryBlock = (void*)((u8*)specs->sFreeListBlock + FreeList::getMemoryRequirement(size));
        specs->sFreeList.Init(size);
        Manager::Memory::lzero(specs->sMemoryBlock, size);
        return true;
    }
    b8 Allocator::Destroy()
    {
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        specs->sFreeList.Destroy();
        Manager::Memory::lzero(specs->sMemoryBlock, specs->sTotalSize);
        specs->sTotalSize = 0;
        mMemory = 0;
        return true;
    }
    void* Allocator::allocate(u64 size)
    {
        return allocateWithAlignment(size, DEFAULT_ALIGNMENT);
    }
    void* Allocator::allocateWithAlignment(u64 size, u16 alignment)
    {
        if(size && alignment)
        {
            AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
            u64 headerSize = sizeof(AllocatorHeader);
            u64 storageSize = sizeof(u32);
            u64 requiredSize = alignment + headerSize + storageSize + size;
            if (requiredSize > 4294967295U)
                return nullptr;
            u64 initialOffset = specs->sFreeList.allocateBlock(requiredSize);
            if (initialOffset < 1)
            {
                std::cout<<"Failed to allocate, Only " << specs->sFreeList.getFreeSpace() << " is available!\n";
                return nullptr;
            }
            void* ptr =  reinterpret_cast<void*>((u64)specs->sMemoryBlock + initialOffset);
            initialOffset = Allocator::alignAddress((u64)ptr + sizeof(u32), alignment);
            u32* blockSize = reinterpret_cast<u32*>(initialOffset - sizeof(u32));
            *blockSize = static_cast<u32>(size);
            AllocatorHeader* header = reinterpret_cast<AllocatorHeader*>(initialOffset + size);
            header->start = ptr;
            header->alignment = alignment;
            return reinterpret_cast<void*>(initialOffset);
        }
        std::cout<< "invalid size or alignment\n";
        return nullptr;
    }
    u64 Allocator::getFreeSpace()
    {
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        return specs->sFreeList.getFreeSpace();
    }
    u64 Allocator::getTotalSpace()
    {
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        return specs->sTotalSize;
    }
}}
