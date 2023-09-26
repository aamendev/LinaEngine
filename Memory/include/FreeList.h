#pragma once
#include "Memory.h"
#include "../../Types.h"
namespace Lina { namespace Memory{
    struct Node
    {
        u64 size;
        u64 offset;
        Node* next;
    };
    struct ListSpecs
    {
        u64 sTotalSize;
        u64 sMaxEntries;
        Node* sHead;
        Node* sNodes;
    };
    class FreeList
    {
        public:
            void* mMemory;
            u64 mTopMarker;
        public:
            /**
             * @brief: empty constructor.
             */
            FreeList(){}
            /**
             * @brief: empty destrucotr.
             */
            ~FreeList(){}
            /**
             * @brief: custom construction function
             * @return: true on success, false on failue.
             */
            b8 Init(u64 totalSize, void* block);
            /**
             * @brief: custom destructor function.
             * @return: true on success, false on failue.
             */
            b8 Destroy();
            /**
             * @brief: Allocates memory of a given size at a given offset in the list.
             * @para: size -> the size of allocated block.
             * @return: true on success, false on failure.
             */
            u64 allocateBlock(u64 size);
            /**
             * @brief: Frees a memory block at a given offset of a given size.
             * @para: size -> size of the block to be freed.
             * @para: offset -> position of the block.
             * @return: true on success, false on failue.
             */
            b8 freeBlock(u64 size, u64 offset);
            /**
             * @brief: clears all the elements in the list.
             */
            void clear();
            /**
             * @brief: Sets the offset and the size value to the INVALID flag.
             * @para: node -> the node to invalidate.
             */
            static void Invalidate(Node* node);
        public:
            u64 getFreeSpace();
            static u64 getMemoryRequirement(u64 totalSize);
            Node* getNode();
            friend class DynamicAllocator;
    };
}}
