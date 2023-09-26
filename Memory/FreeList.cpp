#include "include/FreeList.h"
#define INVALID 2348323453u
namespace Lina{ namespace Memory{

    u64 FreeList::getMemoryRequirement(u64 totalSize)
    {
        u64 maxEntries = totalSize / (sizeof(void*) * sizeof(Node));
        return sizeof(ListSpecs) + (sizeof(Node) * maxEntries);
    }
    b8 FreeList::Init(u64 totalSize, void* block)
    {
        u64 maxEntries = totalSize / (sizeof(void*) * sizeof(Node));
        u64 memoryRequirement = FreeList::getMemoryRequirement(totalSize);
        u64 minimumSize = (sizeof(ListSpecs) + sizeof(Node)) * 8;
        if (totalSize < minimumSize)
        {
            std::cout<< "Too wasteful, did not Create List!\n";
            std::cout<<"Minimum: " << minimumSize << ", Allocated: " << totalSize;
            return false;
        }
        mMemory = block;
        Manager::Memory::lzero(mMemory, memoryRequirement);
        ListSpecs* specs = (ListSpecs*)mMemory;
        specs->sNodes = reinterpret_cast<Node*>((u8*)mMemory + sizeof(ListSpecs));
        specs->sMaxEntries = maxEntries;
        specs->sTotalSize = totalSize;

        specs->sHead = &specs->sNodes[0];
        specs->sHead->offset = 0;
        specs->sHead->size = totalSize;
        specs->sHead->next = 0;

        for (u64 i = 1; i < maxEntries; i++)
        {
            specs->sNodes[i].offset = INVALID;
            specs->sNodes[i].size = INVALID;
        }
        return true;
    }
    b8 FreeList::Destroy()
    {
        if (mMemory)
        {
            ListSpecs* specs = (ListSpecs*)mMemory;
            Manager::Memory::lfree(mMemory, FreeList::getMemoryRequirement(specs->sTotalSize));
            return true;
        }
        return false;
    }
    void FreeList::Invalidate(Node* node)
    {
        node->offset = INVALID;
        node->size = INVALID;
        node->next = 0;
    }
    u64 FreeList::allocateBlock(u64 size)
    {
        if (!mMemory)
            return false;
        ListSpecs* specs = (ListSpecs*)mMemory;
        u64 nodeOffset = 0;
        Node* node = specs->sHead;
        Node* prev = 0;
        while(node)
        {
            if (node->size == size)
            {
                nodeOffset = node->offset;
                Node* returnNode = 0;

                if (prev)
                {
                    prev->next = node->next;
                    returnNode = node;
                }
                else
                {
                    returnNode = specs->sHead;
                    specs->sHead = node->next;
                }
                FreeList::Invalidate(returnNode);
                return nodeOffset;
            }
            else if (node->size > size)
            {
                nodeOffset = node->offset;
                node->size -= size;
                node->offset += size;
                return nodeOffset;
            }
            prev = node;
            node = node->next;
        }
        u64 freeSpace = getFreeSpace();
        std::cout<< "Not enough space. Available Space: "<<freeSpace << '\n';
        return INVALID;
    }
    b8 FreeList::freeBlock(u64 size, u64 offset)
    {
        if (!size || !mMemory)
            return false;
        ListSpecs* specs = (ListSpecs*)mMemory;
        Node* node = specs->sHead;
        Node* prev = 0;
        if (!node)
        {
            Node* newHead = getNode();
            newHead->offset = offset;
            newHead->size = size;
            newHead->next = 0;
            specs->sHead = newHead;
        }
        else
        {
            while(node)
            {
                if (node->offset + node->size == offset)
                {
                    node->size += size;
                    if (node->next && node->next->offset == node->offset + node->size)
                    {
                        node->size += node->next->size;
                        Node* next = node->next;
                        node->next = node->next->next;
                        FreeList::Invalidate(next);
                    }
                    return true;
                }
                else if (node->offset == offset)
                {
                    std::cout<<"Double free of Node at: " << offset << '\n';
                    return false;
                }
                else if (node->offset > offset)
                {
                    Node* newNode = getNode();
                    newNode->offset = offset;
                    newNode->size = size;
                    if (prev)
                    {
                        prev->next = newNode;
                        newNode->next = node;
                    }
                    else
                    {
                        newNode->next = node;
                        specs->sHead = newNode;
                    }
                    if (newNode->next && newNode->next->offset == newNode->offset + newNode->size)
                    {
                        newNode->size += newNode->next->size;
                        Node* rubbishNode = newNode->next;
                        newNode->next = newNode->next->next;
                        FreeList::Invalidate(rubbishNode);
                    }
                    if (prev && newNode->offset == prev->offset + prev->size)
                    {
                        prev->size += newNode->size;
                        Node* rubbishNode = newNode;
                        prev->next = rubbishNode->next;
                        FreeList::Invalidate(rubbishNode);
                    }
                    return true;
                }
                prev = node;
                node = node->next;
            }
        }
        std::cout<<"Memory Corruption, could not free!\n";
        return false;
    }
    void FreeList::clear()
    {
        if (!mMemory)
            return;
        ListSpecs* specs = (ListSpecs*)mMemory;

        for (u64 i = 1; i < specs->sMaxEntries; i++)
        {
            Invalidate(&specs->sNodes[i]);
        }
        specs->sHead->offset = 0;
        specs->sHead->size = specs->sTotalSize;
        specs->sHead->next = 0;
    }
    Node* FreeList::getNode()
    {
        ListSpecs* specs = (ListSpecs*)mMemory;
        for (u64 i = 1; i < specs->sMaxEntries; i++)
        {
            if (specs->sNodes[i].offset == INVALID)
                return &specs->sNodes[i];
        }
        return 0;
    }
    u64 FreeList::getFreeSpace()
    {
        if (!mMemory)
            return 0;
        u64 current = 0;
        ListSpecs* specs = (ListSpecs*)mMemory;
        Node* node = specs->sHead;
        while (node)
        {
            current += node->size;
            node = node->next;
        }
        return current;
    }
}}
