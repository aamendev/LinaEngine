#include <iostream>
#include <memory>
#include "include/Memory.h"
#include "include/MemoryOverload.h"
#include "include/FreeList.h"
int main(){
    Lina::Manager::MemoryStats stats = Lina::Manager::Memory::Shutdown();
    std::cout<<stats;
	return 0;
}
