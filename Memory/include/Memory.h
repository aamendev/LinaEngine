#pragma once
#include <cstring>
#include <iostream>
#include "../../Types.h"
#include "Allocator.h"
namespace Lina{ namespace Manager{
    /**
     * @brief: enumeration of different memory categories to be grouped.
     */
    enum MemoryCategory
    {
        UNKNOWN = 0,
        TEXTURE,
        APPLICATION,
        RENDERABLE,
        ENTITY,
        TRANSFORM,
        RENDER,
        TAG,
        SCRIPT,
        SCENE,
        MAX
    };

    struct MemoryStats
    {
        u64 totalAllocations;
        u64 totalFrees;
        u64 perCategoryAllocations[MAX];
        u64 currentUsage() {return totalAllocations - totalFrees;}
    };
    struct MemorySpecs
    {
        u64 sTotalSize;
        MemoryStats sStats;
        u64 sMemoryRequirement;
        Lina::Allocation::Allocator sAllocator;
        void* sAllocatorBlock;
    };
    class Memory
    {
        public:
            /**
             * @brief: empty constructor
             */
            Memory(){}
            /**
             * @brief: empty destructor.
             */
            ~Memory(){}
            /**
             * @brief: custom constructor.
             */
            b8 Init(u64 totalSize);
            /**
             * @brief: custom destructor
             */
            MemoryStats ShutDown();
            /**
             * @brief: allocates memory with a given size. Aligns based on category.
             * @param size -> size of memory block
             * @param category -> memory category
             * @return: void pointer to allocated memory.
             */
            void* lalloc(u64 size, MemoryCategory category = UNKNOWN);
            /**
             * @brief: frees allocated memory block of given size.
             * @param block-> pointer to memory block to be freed.
             * @param size-> size of memory block
             */
            b8 lfree(void* block, u64 size);
            /**
             * @brief: assigns zero to the memory block.
             * @param block -> memory block
             * @param size -> block size.
             * @return: pointer to memory block.
             */
            void* lzero(void* block, u64 size);
            /**
             * @brief: copies memory data between blocks.
             * @param dest -> destination block.
             * @param source -> source block.
             * @size: size of data.
             * @return: pointer to copied data.
             */
            void* lcopy(void* dest, const void* source, u64 size);
            /**
             * @brief: Fills datablock with a value.
             * @param dest -> destination block to be filled.
             * @param value -> value to fill block with.
             * @param size -> size of block.
             * @return: pointer to set memory block.
             */
            void* lset(void* dest, i32 value, u64 size);
            /**
             * @brief: Creates a stack allocator.
             * @param memory -> memory address to store the allocator in.
             * @param size -> size of the stack allocator.
             * @return: true if succeeded, false if not.
             */
             b8 createStackAllocator(void* memory, u64 size);
             std::pair<u64, u16> getSizeAndAlignment(void* block);
             u64 getSize(void* block);
             u16 getAlignment(void* block);
             void* lallocWithAlignment(u64 size, MemoryCategory cat, u16 alignment);
             void destroyStackAllocator();
    };
    std::ostream& operator<<(std::ostream& os, MemoryStats& stat);
    std::ostream& operator<<(std::ostream& os, MemoryStats&& stat);
}}
