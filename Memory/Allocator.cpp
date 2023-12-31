#include "include/Allocator.h"
#include "include/Memory.h"
extern Lina::Manager::Memory gMemoryManager;
namespace Lina{ namespace Allocation{
    u64 Allocator::getMemoryRequirement(u64 size)
    {
        u64 freeListRequirement = FreeList::getMemoryRequirement(size);
        return freeListRequirement + sizeof(AllocatorSpecs) + size;
    }
    b8 Allocator::Init(u64 size, void* block)
    {
        if (size < 1)
            return false;
        mMemory = block;
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        specs->sTotalSize = size;
        specs->sFreeListBlock = (void*)((u8*)mMemory + sizeof(AllocatorSpecs));
        specs->sMemoryBlock = (void*)((u8*)specs->sFreeListBlock + FreeList::getMemoryRequirement(size));
        specs->sFreeList.Init(size, specs->sFreeListBlock);
        gMemoryManager.lzero(specs->sMemoryBlock, size);
        return true;
    }
    b8 Allocator::Destroy()
    {
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        specs->sFreeList.Destroy();
        gMemoryManager.lzero(specs->sMemoryBlock, specs->sTotalSize);
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
        return 0;
    }
    b8 Allocator::free(void* block)
    {
       return freeWithAlignment(block);
    }
    b8 Allocator::freeWithAlignment(void* block)
    {
        if (!block)
        {
            std::cout<<"Invalid Free!\n";
            return false;
        }
        AllocatorSpecs* specs = reinterpret_cast<AllocatorSpecs*>(mMemory);
        if (block < specs->sMemoryBlock || block > (u8*)specs->sMemoryBlock + specs->sTotalSize)
        {
            void* endBlock = (u8*)specs->sMemoryBlock + specs->sTotalSize;
            std::cout<<"Out of Range, Block position: "
                << block << " ,Allocator Range: [" << specs->sMemoryBlock<<", "
                << endBlock<< "]\n\n";
            return false;
        }
        u32* blockSize = (u32*)((u64)block - sizeof(u32));
        AllocatorHeader* header =reinterpret_cast<AllocatorHeader*>((u64)block + *blockSize);
        u64 requiredSize = header->alignment + sizeof(AllocatorHeader) + sizeof(u32) + *blockSize;
        u64 offset = (u64)header->start - (u64)specs->sMemoryBlock;
        if (!specs->sFreeList.freeBlock(requiredSize, offset))
        {
            std::cout<<"Failed to Free the given block\n";
            return false;
        }
        return true;
    }
    std::pair<u64, u16> Allocator::getSizeAndAlignment(void* block)
    {
        u64 size = *(u32*)((u64)block - sizeof(u32));
        AllocatorHeader* header = reinterpret_cast<AllocatorHeader*>((u64)block + size);
        u16 alignment = header->alignment;
        return {size, alignment};
    }
    u64 Allocator::getSize(void* block)
    {
        return getSizeAndAlignment(block).first;
    }
    u16 Allocator::getAlignment(void* block)
    {
        return getSizeAndAlignment(block).second;
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
