#include "MemorySimulator.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    MemorySimulator memSim;
    std::string line;

    std::cout << "Memory Management Simulator\n";  
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line) || line == "exit") break;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "init") {
            std::string sub, val;
            ss >> sub >> val;
            if (sub == "memory") memSim.initMemory(std::stoul(val));
        } 
        else if (cmd == "config") {
            std::string sub;
            size_t l1, l2;
            ss >> sub >> l1 >> l2;
            if (sub == "cache") memSim.configCache(l1, l2);
        }
        else if (cmd == "set") {
            std::string sub, arg1, arg2;
            ss >> sub >> arg1; 
            
            if (sub == "allocator") {
                if (arg1 == "first_fit" || arg1 == "first") {
                    if (arg1 == "first" && (ss >> arg2) && arg2 != "fit") 
                    memSim.setStrategy(FIRST_FIT);
                }
                else if (arg1 == "best_fit" || arg1 == "best") {
                    if (arg1 == "best" && (ss >> arg2) && arg2 != "fit") {}
                    memSim.setStrategy(BEST_FIT);
                }
                else if (arg1 == "worst_fit" || arg1 == "worst") {
                    if (arg1 == "worst" && (ss >> arg2) && arg2 != "fit") {}
                    memSim.setStrategy(WORST_FIT);
                }
            }
        }
        else if (cmd == "malloc") {
            size_t s; ss >> s; memSim.allocate(s);
        }
        else if (cmd == "free") {
            int id; ss >> id; memSim.deallocate(id);
        }
        else if (cmd == "access") {
            size_t addr; ss >> addr; memSim.accessMemory(addr);
        }
        else if (cmd == "dump") {
            std::string sub; ss >> sub;
            if (sub == "memory") memSim.dumpMemory();
        }
        else if (cmd == "stats") {
            memSim.printStats();
        }
    }
    return 0;
}