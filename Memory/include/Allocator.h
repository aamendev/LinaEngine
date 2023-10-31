#pragma once
#include "FreeList.h"
#include "../../Types.h"
#define DEFAULT_ALIGNMENT (16)
namespace Lina { namespace Allocation{
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
            b8 Init(u64 size, void* block);
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
            /**
             * @brief returns the memory requirement for the allocator.
             * @param size -> the total size to be used by the allocator.
             * @return the required size.
             */
            static u64 getMemoryRequirement(u64 size);
            /**
             * @brief Frees a given memory block. Delegates the call to freeWithAlignment.
             * @param block -> block to be freed.
             * @return true on success, false on failure.
             */
            b8 free(void* block);
            /**
             * @brief Frees a given memory block.
             * @param block -> block to be freed.
             * @return true on success, false on failue.
             */
            b8 freeWithAlignment(void* block);
            /**
             * @brief gets the total remaining free space from the allocator.
             * @return the amount of free space.
             */
            u64 getFreeSpace();
            /**
             * @brief gets the size and the alignment of the given block.
             * @param block -> block to get the size an alignment of.
             * @return a pair of the form (size, alignment).
             */
            std::pair<u64, u16> getSizeAndAlignment(void*block);
            u64 getSize(void* block);
            u16 getAlignment(void* block);
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
            friend class Memory;
    };
}}

