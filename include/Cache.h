#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstddef>

struct CacheLine {
    bool valid;
    unsigned long tag;
};

class CacheLevel {
private:
    size_t size;
    size_t blockSize;
    int associativity;
    size_t numSets;

    struct Set {
        std::vector<CacheLine> lines;
        int nextToReplace; 
    };

    std::vector<Set> sets;
    
    size_t hits;
    size_t misses;

public:
    CacheLevel(size_t size, size_t blockSize, int associativity);
    
    bool access(size_t address);
    void printStats();
};

#endif