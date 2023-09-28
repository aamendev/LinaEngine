#pragma once
#include "FreeList.h"
#include "Memory.h"
#define DEFAULT_ALIGNMENT (16)
namespace Lina { namespace Memory{
    struct AllocatorSpecs
    {
        u64 sTotalSize;
        FreeList sFreeList;
        void* sFreeListBlock;
        void* sMemoryBlock;
    };
    struct AllocatorHeader
    {
        void* start;
        u16 alignment;
    };
    class Allocator
    {
        public:
            /**
             * @brief: empty constructor, to be replaced with custom function.
             */
            Allocator() {}
            /**
             * @brief: empty destructor, to be replaces with custom destructor
             */
            ~Allocator() {}
            /**
             * @brief: custom constructor. Creates an Allocator with a maximum size.
             * @param size -> maximum possible allocation size.
             * @return: true on success, false on failure.
             */
            b8 Init(u64 size);
            /**
             * @brief: custom destructor. Zeros all memory that was once allocated.
             * @return: true (always success).
             */
            b8 Destroy();
            /**
             * @brief: allocates memory of a given size with defauly alignment of 16.
             * @return: pointer to allocated memory.
             */
            void* allocate(u64 size);
            /**
             * @brief allocates memory of certain size with certain alignment.
             * @param size -> size of memory block.
             * @param alignment -> alignment requirement of allocated block.
             * @return a pointer to the aligned block.
             */
            void* allocateWithAlignment(u64 size, u16 alignment);
            b8 freeBlock();
            b8 clear();
            u64 getMemoryRequirement(u64 size);
            /**
             * @brief gets the total remaining free space from the allocator.
             * @return the amount of free space.
             */
            u64 getFreeSpace();
            /**
             * @brief gets the total space acquired by the allocator.
             * @return the total allocated space.
             */
            u64 getTotalSpace();
            /**
             * @brief gets the header size.
             * @return header size.
             */
            static inline u64 getHeaderSize()
            {
                return sizeof(AllocatorHeader) + sizeof(u32);
            }
        private:
            /**
             * @brief gets the aligned address from the operand witha given alignment.
             * @param operand -> u64 representaiton of pointer to unaligned address.
             * @param alignment -> alignment desired. Should be a power of 2.
             * @return u64 representaiton of new aligned address.
             */
            static inline u64 alignAddress(u64 operand, u16 alignment)
            {
                return (operand + alignment - 1) & ~(alignment - 1);
            }
            /**
             * @brief gets a pointer representaiton of the aligned address.
             * @param pointer -> pointer to unaligned address.
             * @param alignment -> desired alignment. Should be a power of 2.
             * @return a void pointer to the aligned address.
             */
            static inline void* alignPointer(void* pointer, u16 alignment)
            {
                 return reinterpret_cast<void*>(alignAddress((u64)pointer, alignment));
            }
        private:
            void* mMemory;
    };
}}
