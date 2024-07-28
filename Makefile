# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2
LDFLAGS =
TARGET = ascii-art.bin
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

