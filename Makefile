# Compile settings
CXX = g++
CXXFLAGS = -I"C:/SFML/SFML-3.0.0/include" -DSFML_STATIC
LDFLAGS = -L"C:/SFML/SFML-3.0.0/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

# Get all source files and object files
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

# Final executable
TARGET = game.exe

# Default rules
all: $(TARGET) clean_objs

# Compile all source files to object files
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files to final executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Delete all object files
clean_objs:
	del /F $(OBJ_FILES)

# Clean everything
clean:
	del /F $(OBJ_FILES) $(TARGET)
