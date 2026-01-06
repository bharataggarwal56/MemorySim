@echo off
echo ==========================================
echo      RUNNING MEMORY SIMULATOR TESTS
echo ==========================================

REM 
if not exist memsim.exe (
    echo [ERROR] memsim.exe not found!
    echo Please compile first: g++ -Iinclude src/main.cpp src/allocator/MemorySimulator.cpp src/cache/Cache.cpp -o memsim
    pause
    exit /b
)

echo.
echo [TEST 1] Running Fragmentation Test...
if exist tests\workload_fragmentation.txt (
    memsim.exe < tests\workload_fragmentation.txt > tests\log_fragmentation.txt
    echo [SUCCESS] Output saved to tests\log_fragmentation.txt
) else (
    echo [ERROR] tests\workload_fragmentation.txt not found.
)

echo.
echo [TEST 2] Running Cache Locality Test...
if exist tests\workload_cache_locality.txt (
    memsim.exe < tests\workload_cache_locality.txt > tests\log_cache.txt
    echo [SUCCESS] Output saved to tests\log_cache.txt
) else (
    echo [ERROR] tests\workload_cache_locality.txt not found.
)

echo.
echo ==========================================
echo All tests complete. Check the tests folder for logs.
pause