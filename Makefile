CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

SRCS = src/main.cpp src/allocator/MemorySimulator.cpp src/cache/Cache.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = memsim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)