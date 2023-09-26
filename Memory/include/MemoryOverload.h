#pragma once
#include "./Memory.h"
#include <memory>

void* operator new(u64 size)
{
    return Lina::Manager::Memory::lalloc(size);
}
void operator delete(void* block, u64 size)
{
    Lina::Manager::Memory::lfree(block, size);
}
void operator delete[](void* block, u64 size)
{
    Lina::Manager::Memory::lfree(block, size);
}
void operator delete[](void* block)
{
    Lina::Manager::Memory::lfree(block, 0);
}
void operator delete(void* block)
{
    Lina::Manager::Memory::lfree(block, 0);
}
