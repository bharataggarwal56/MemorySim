#include "Cache.h"
#include <cmath>
#include <iostream>

CacheLevel::CacheLevel(size_t size, size_t blockSize, int associativity)
    : size(size), blockSize(blockSize), associativity(associativity), hits(0), misses(0) {

    size_t totalBlocks = size / blockSize;
    numSets = totalBlocks / associativity;
    
    sets.resize(numSets);
    for (auto& set : sets) {
        set.lines.resize(associativity);
        set.nextToReplace = 0; 
        for (auto& line : set.lines) {
            line.valid = false;
            line.tag = 0;
        }
    }
}

bool CacheLevel::access(size_t address) {
    size_t blockOffsetBits = (size_t)std::log2(blockSize);
    size_t setIndexBits = (size_t)std::log2(numSets);
    
    size_t setIndexMask = (1 << setIndexBits) - 1;
    size_t setIndex = (address >> blockOffsetBits) & setIndexMask;
    unsigned long tag = address >> (blockOffsetBits + setIndexBits);
    
    auto& set = sets[setIndex];
    for (const auto& line : set.lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            return true; 
        }
    }
    
    misses++;

    int victimIndex = set.nextToReplace;
    set.lines[victimIndex].valid = true;
    set.lines[victimIndex].tag = tag;
    set.nextToReplace = (set.nextToReplace + 1) % associativity;
    
    return false; 
}

void CacheLevel::printStats() {
    std::cout << "  Hits: " << hits << ", Misses: " << misses;
    if (hits + misses > 0) {
        double ratio = (double)hits / (hits + misses) * 100.0;
        std::cout << " (Hit Ratio: " << ratio << "%)";
    }
    std::cout << "\n";
}