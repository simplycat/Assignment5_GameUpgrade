# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Executable name
TARGET = game

# Source files - MUST include ALL .cpp files
SRC = main.cpp game.cpp player.cpp enemy.cpp protection.cpp

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compiling all source files..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "Compilation complete."

run: $(TARGET)
	@echo "Running game..."
	./$(TARGET)

test: $(TARGET)
	@echo "Running autograder..."
	chmod +x test.sh
	./test.sh

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) *.o *.txt
	@echo "Clean complete."
