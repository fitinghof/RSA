# Folders
BINARYFOLDER = binary
SOURCEFOLDER = source
HEADERFOLDER = headers

# Source files
SOURCES = $(wildcard $(SOURCEFOLDER)/*.cpp)
HEADERS = $(wildcard $(HEADERFOLDER)/*.hpp)

# Object files
OBJECTS = $(patsubst $(SOURCEFOLDER)/%.cpp, $(BINARYFOLDER)/%.o, $(SOURCES))

# Executable output
OUTPUT = main.exe
MAIN = $(SOURCEFOLDER)/main.cpp  # Corrected path

# Compiler settings
ARGS = -Wall -O2
CC = g++

# Default target
default: $(OUTPUT)

# Run target
run: $(OUTPUT)
	./$(OUTPUT)

# Link the final executable
$(OUTPUT): $(OBJECTS)
	$(CC) $(ARGS) -o $@ $^ -lgmp -lgmpxx

# Compile each source file into an object file
$(BINARYFOLDER)/%.o: $(SOURCEFOLDER)/%.cpp
	@mkdir -p $(BINARYFOLDER)  # Ensure binary folder exists
	$(CC) $(ARGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BINARYFOLDER)/*.o $(OUTPUT)

.PHONY: default run clean
