CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -pthread -Iinclude -Iinclude/sensor

TARGET = bin/smart_gateway

SOURCES = $(shell find src -name "*.cpp")

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -rf bin

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
