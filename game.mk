GAME_NAME := game
GAME_DIR := $(GAME_NAME)
GAME_SRC := $(notdir $(wildcard $(GAME_DIR)/*.cpp))
GAME_OBJ := $(addprefix $(BUILD_DIR)/$(GAME_NAME)/, $(GAME_SRC:.cpp=.o))

GAME_INC := -I. -I$(GAME_DIR)
GAME_BIN := $(BIN_DIR)/$(GAME_NAME)

# Ejecutable del juego, depende de los objetos y de la librería engine
$(GAME_BIN): $(GAME_OBJ) $(ENGINE_LIB) | $(BIN_DIR) $(BUILD_DIR)/$(GAME_NAME)
	$(CXX) $(CXXFLAGS) $(GAME_INC) -o $@ $^ -lsystemd

# Compilar objetos game
$(BUILD_DIR)/$(GAME_NAME)/%.o: $(GAME_DIR)/%.cpp | $(BUILD_DIR)/$(GAME_NAME)
	$(CXX) $(CXXFLAGS) $(GAME_INC) -c $< -o $@

# Crear directorio build game si no existe
$(BUILD_DIR)/$(GAME_NAME):
	mkdir -p $@
$(BIN_DIR):
	mkdir -p $@
print-%:
	@echo '$*=$($*)'
