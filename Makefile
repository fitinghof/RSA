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

# Compiler settings
ARGS = -std=c++17 -Wall -O0
CC = g++
LIBS = -L/usr/local/lib -lgmp -lgmpxx  # Adjusted for your GMP installation

# Default target
default: $(OUTPUT)

# Run target
run: $(OUTPUT)
	./$(OUTPUT)

# Link the final executable
$(OUTPUT): $(OBJECTS)
	$(CC) -static $(ARGS) -o $@ $^ $(LIBS)

# Compile each source file into an object file
$(BINARYFOLDER)/%.o: $(SOURCEFOLDER)/%.cpp $(HEADERS)
	@mkdir -p $(BINARYFOLDER)  # Ensure binary folder exists
	$(CC) $(ARGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BINARYFOLDER)/*.o $(OUTPUT)

.PHONY: default run clean
