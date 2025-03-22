# Variables
BUILD_DIR := build
TARGET := ./$(BUILD_DIR)/main
SOURCES :=Bunny.cpp Doe.cpp Kit.cpp View.cpp Controller.cpp main.cpp
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
PYTHON_SCRIPT := dataFancyDisplay.py

# Default target
all: $(BUILD_DIR) $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Phony targets
.PHONY: clean run watch

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the built executable
run: all
	./$(TARGET) 2>data.py

# Watch (execute the Python script)
watch:
	python3 $(PYTHON_SCRIPT)
