#include "MemorySimulator.h"
#include <iostream>
#include <iomanip>

MemorySimulator::MemorySimulator()
    : totalSize(0), nextBlockId(1), currentStrategy(FIRST_FIT),
      l1Cache(nullptr), l2Cache(nullptr),
      successfulAllocations(0), failedAllocations(0) {}

MemorySimulator::~MemorySimulator()
{
    if (l1Cache)
        delete l1Cache;
    if (l2Cache)
        delete l2Cache;
}

void MemorySimulator::initMemory(size_t size)
{
    totalSize = size;
    physicalMemory.resize(totalSize, 0);

    memoryList.clear();
    Block initialBlock;
    initialBlock.id = 0;
    initialBlock.startAddr = 0;
    initialBlock.size = totalSize;
    initialBlock.isFree = true;
    memoryList.push_back(initialBlock);

    std::cout << "Memory initialized. Default strategy: First Fit\n";
}

void MemorySimulator::initCache(size_t l1Size, size_t l2Size)
{
    if (l1Cache)
        delete l1Cache;
    if (l2Cache)
        delete l2Cache;

    l1Cache = new CacheLevel(l1Size, 64, 1);
    l2Cache = new CacheLevel(l2Size, 64, 2);

    std::cout << "Cache L1 initialized: " << l1Size << "B size, 64B block, Direct-Mapped.\n";
    std::cout << "Cache L2 initialized: " << l2Size << "B size, 64B block, 2-Way Set-Associative.\n";
}

void MemorySimulator::configCache(size_t l1Size, size_t l2Size)
{
    std::cout << "Reconfiguring Caches...\n";
    initCache(l1Size, l2Size);
}

void MemorySimulator::setStrategy(Strategy s)
{
    currentStrategy = s;
    std::cout << "Allocator strategy set.\n";
}

void MemorySimulator::allocate(size_t size)
{
    auto bestBlockIt = memoryList.end();

    // STRATEGY 1: FIRST FIT
    if (currentStrategy == FIRST_FIT)
    {
        for (auto it = memoryList.begin(); it != memoryList.end(); ++it)
        {
            if (it->isFree && it->size >= size)
            {
                bestBlockIt = it;
                break;
            }
        }
    }
    // STRATEGY 2: BEST FIT
    else if (currentStrategy == BEST_FIT)
    {
        size_t minDiff = -1;
        for (auto it = memoryList.begin(); it != memoryList.end(); ++it)
        {
            if (it->isFree && it->size >= size)
            {
                size_t diff = it->size - size;
                if (diff < minDiff)
                {
                    minDiff = diff;
                    bestBlockIt = it;
                }
            }
        }
    }
    // STRATEGY 3: WORST FIT
    else if (currentStrategy == WORST_FIT)
    {
        size_t maxDiff = 0;
        bool foundAny = false;
        for (auto it = memoryList.begin(); it != memoryList.end(); ++it)
        {
            if (it->isFree && it->size >= size)
            {
                size_t diff = it->size - size;
                if (diff >= maxDiff || !foundAny)
                {
                    maxDiff = diff;
                    bestBlockIt = it;
                    foundAny = true;
                }
            }
        }
    }

    if (bestBlockIt != memoryList.end())
    {
        if (bestBlockIt->size > size)
        {
            Block newFreeBlock;
            newFreeBlock.id = 0;
            newFreeBlock.startAddr = bestBlockIt->startAddr + size;
            newFreeBlock.size = bestBlockIt->size - size;
            newFreeBlock.isFree = true;
            memoryList.insert(std::next(bestBlockIt), newFreeBlock);
            bestBlockIt->size = size;
        }

        bestBlockIt->isFree = false;
        bestBlockIt->id = nextBlockId++;
        std::cout << "Allocated block id=" << bestBlockIt->id
                  << " at address=0x"
                  << std::uppercase << std::hex << std::setw(4) << std::setfill('0')
                  << bestBlockIt->startAddr
                  << std::dec << "\n";

        successfulAllocations++;
    }
    else
    {
        std::cout << "Error: Not enough memory.\n";
        failedAllocations++;
    }
}

void MemorySimulator::deallocate(int id)
{
    auto it = memoryList.begin();
    bool found = false;

    while (it != memoryList.end())
    {
        if (!it->isFree && it->id == id)
        {
            found = true;
            break;
        }
        ++it;
    }

    if (!found)
    {
        std::cout << "Error: Block id " << id << " not found.\n";
        return;
    }

    it->isFree = true;
    it->id = 0;

    bool merged = false;

    auto nextIt = std::next(it);
    if (nextIt != memoryList.end() && nextIt->isFree)
    {
        it->size += nextIt->size;
        memoryList.erase(nextIt);
        merged = true;
    }

    if (it != memoryList.begin())
    {
        auto prevIt = std::prev(it);
        if (prevIt->isFree)
        {
            prevIt->size += it->size;
            memoryList.erase(it);
            merged = true;
        }
    }

    std::cout << "Block " << id << " freed";
    if (merged)
        std::cout << " and merged";
    std::cout << "\n";
}

void MemorySimulator::accessMemory(size_t address)
{
    if (address >= totalSize)
    {
        std::cout << "Segmentation Fault: Address out of bounds.\n";
        return;
    }

    if (!l1Cache)
    {
        initCache(64, 256);
    }

    bool l1Hit = l1Cache->access(address);
    if (l1Hit)
    {
        std::cout << "L1 Cache Hit at address " << address << "\n";
    }
    else
    {
        std::cout << "L1 Miss. Checking L2...\n";
        bool l2Hit = l2Cache->access(address);
        if (l2Hit)
        {
            std::cout << "L2 Cache Hit at address " << address << "\n";
        }
        else
        {
            std::cout << "L2 Miss. Accessing Main Memory...\n";
        }
    }
}
void MemorySimulator::dumpMemory()
{
    for (const auto &block : memoryList)
    {
        size_t endAddr = block.startAddr + block.size - 1;

        std::cout << "["
                  << "0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << block.startAddr
                  << " - "
                  << "0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << endAddr
                  << "] " << std::dec;

        if (block.isFree)
        {
            std::cout << "FREE\n";
        }
        else
        {
            std::cout << "USED (id=" << block.id << ")\n";
        }
    }
}

void MemorySimulator::printStats()
{
    size_t usedMemory = 0;
    size_t freeMemory = 0;
    size_t largestFreeBlock = 0;

    for (const auto &block : memoryList)
    {
        if (block.isFree)
        {
            freeMemory += block.size;
            if (block.size > largestFreeBlock)
            {
                largestFreeBlock = block.size;
            }
        }
        else
        {
            usedMemory += block.size;
        }
    }

    double fragmentation = 0.0;
    if (freeMemory > 0)
    {
        fragmentation = 1.0 - ((double)largestFreeBlock / freeMemory);
    }

    std::cout << "Total memory: " << totalSize << "\n";
    std::cout << "Used memory: " << usedMemory << "\n";
    std::cout << "External fragmentation: " << (fragmentation * 100.0) << "%\n";
    std::cout << "Internal fragmentation: 0%\n";

    std::cout << "Allocation success: " << successfulAllocations << "\n";
    std::cout << "Allocation failures: " << failedAllocations << "\n";

    if (l1Cache)
        l1Cache->printStats();
    if (l2Cache)
        l2Cache->printStats();
}