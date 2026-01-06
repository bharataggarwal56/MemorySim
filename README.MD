```markdown
# Memory Management Simulator

A C++ simulation of an Operating System's memory management unit. This project implements physical memory allocation strategies (First Fit, Best Fit, Worst Fit) and a multilevel CPU cache hierarchy (L1/L2) with FIFO replacement.

## Features
* **Memory Allocator**: Custom implementation of `malloc` and `free` with block splitting and coalescing.
* **Strategies**: First Fit, Best Fit, Worst Fit.
* **Cache Hierarchy**: Simulated L1 (Direct-Mapped) and L2 (2-Way Set-Associative) caches.
* **Metrics**: Real-time reporting of fragmentation and cache hit/miss ratios.

## How to Build
Compile the project using `g++`.

**g++ (Windows/Linux)**
```bash
g++ -Iinclude src/main.cpp src/allocator/MemorySimulator.cpp src/cache/Cache.cpp -o memsim

```

## How to Run

Start the interactive CLI:

```bash
./memsim

```

## Testing

To run the automated tests (Fragmentation & Cache locality tests):

* Run `test.bat`.

```

```