# Setări pentru compilare
CXX = g++
CXXFLAGS = -I"C:/SFML/SFML-3.0.0/include" -DSFML_STATIC
LDFLAGS = -L"C:/SFML/SFML-3.0.0/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

# Detectează automat fișierele sursă și creează obiecte
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

# Executabil final
TARGET = game.exe

# Regula principală
all: $(TARGET) clean_objs

# Regula pentru compilare
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regula pentru link-editare
$(TARGET): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Șterge fișierele obiect după link-editare
clean_objs:
	del /F $(OBJ_FILES)

# Regula pentru curățare completă
clean:
	del /F $(OBJ_FILES) $(TARGET)
