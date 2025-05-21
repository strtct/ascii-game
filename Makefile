# Variables comunes
BUILD_DIR := build
BIN_DIR := bin
LIB_DIR := lib


include engine.mk
include game.mk

.PHONY: all clean directories game
all: directories $(ENGINE_LIB) $(GAME_BIN)

game: directories $(GAME_BIN)
directories: $(BUILD_DIR)/engine $(BUILD_DIR)/game $(BIN_DIR) $(LIB_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)

#directories:
#	@mkdir -p $(BUILD_DIR)/engine
#	@mkdir -p $(BUILD_DIR)/game
#	@mkdir -p $(BIN_DIR)
#	@mkdir -p $(LIB_DIR)
