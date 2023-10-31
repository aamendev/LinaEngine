#pragma once
#include <iostream>
#include <memory>
#include "./Memory.h"
extern Lina::Manager::Memory gMemoryManager;
/*inline void* operator new(u64 size)
{
     return gMemoryManager.lalloc(size);
}
inline void* operator new[](u64 size)
{
    return gMemoryManager.lalloc(size);
}
inline void operator delete(void* block, u64 size)
{
    gMemoryManager.lfree(block, size);
}
inline void operator delete[](void* block, u64 size)
{
    std::cout<<gMemoryManager.lfree(block, size);
}
inline void operator delete[](void* block)
{
    u64 size = gMemoryManager.getSize(block);
    gMemoryManager.lfree(block, size);
}
inline void operator delete(void* block)
{
    u64 size = gMemoryManager.getSize(block);
    gMemoryManager.lfree(block, size);
}*/
template <typename T>
inline T* lnew ()
{
    return reinterpret_cast<T*>(gMemoryManager.lalloc((u64)sizeof(T)));
}
template <class T>
inline T* lnew (T&& t)
{
    T* newT = new (gMemoryManager.lalloc((u64)sizeof(T))) T(t);
    std::cout<<"Copied::::"<<typeid(T).name()<<"\n";
    return newT;
}
template <class T>
inline T* lnew (const T& t)
{
    T* newT = new (gMemoryManager.lalloc((u64)sizeof(T))) T(t);
    std::cout<<"Copied2::::"<<typeid(T).name()<<"\n";
    return newT;
}
template <typename T>
inline void ldelete (T* block)
{
    block->~T();
    gMemoryManager.lfree(block, gMemoryManager.getSize(block));
}
