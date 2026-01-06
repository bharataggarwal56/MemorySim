# 💾 Memory Management Simulator

A C++ simulation of an Operating System’s memory management system.  
This project demonstrates **physical memory allocation strategies** and a **multilevel CPU cache hierarchy**, helping visualize core OS concepts such as fragmentation, allocation policies, and cache locality.

---

## 🚀 Project Overview

The goal of this project is to simulate how an operating system manages physical memory and CPU caches.  
The simulator provides a simplified yet realistic model of memory allocation, deallocation, and cache lookup behavior, making it suitable for academic learning and demonstrations.

---

## ✨ Key Features

- ⚙️ Custom implementation of `malloc` and `free`  
- 📐 Allocation strategies:
  - First Fit  
  - Best Fit  
  - Worst Fit  
- 🧩 Memory block splitting and coalescing  
- 💾 Cache hierarchy:
  - **L1 Cache** – Direct-Mapped  
  - **L2 Cache** – 2-Way Set-Associative  
- 🔁 FIFO (First-In, First-Out) cache replacement policy  
- 📊 Fragmentation and cache hit/miss statistics  

---

## 🛠️ Build Instructions

Compile the project using `g++`:

```bash
g++ -Iinclude src/main.cpp src/allocator/MemorySimulator.cpp src/cache/Cache.cpp -o memsim
```

---

## ▶️ Run

Start the simulator using the command below:

```bash
./memsim
```

The program launches an interactive CLI to perform memory operations and view statistics.

---

## 🧪 Testing

Run the automated tests for memory fragmentation and cache behavior:

```bash
test.bat
```
