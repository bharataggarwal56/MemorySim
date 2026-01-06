#ifndef MEMORY_SIMULATOR_H
#define MEMORY_SIMULATOR_H

#include <vector>
#include <list>
#include <cstddef>
#include "Cache.h"

enum Strategy { FIRST_FIT, BEST_FIT, WORST_FIT };

struct Block {
    int id;
    size_t startAddr;
    size_t size;
    bool isFree;
};

class MemorySimulator {
private:
    std::vector<char> physicalMemory;
    std::list<Block> memoryList;
    size_t totalSize;
    int nextBlockId;
    Strategy currentStrategy;
    
    size_t successfulAllocations;
    size_t failedAllocations;

    CacheLevel* l1Cache;
    CacheLevel* l2Cache;

public:
    MemorySimulator();
    ~MemorySimulator();
    
    void initMemory(size_t size);
    void initCache(size_t l1Size, size_t l2Size);

    void configCache(size_t l1Size, size_t l2Size); 

    void setStrategy(Strategy s);
    void allocate(size_t size);
    void deallocate(int id);
    void accessMemory(size_t address);
    
    void dumpMemory();
    void printStats();
};

#endif