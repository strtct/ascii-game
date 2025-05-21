ENGINE_NAME := engine
ENGINE_DIR := $(ENGINE_NAME)
ENGINE_SRC := $(wildcard $(ENGINE_DIR)/*.cpp) $(wildcard $(ENGINE_DIR)/*/*.cpp)
ENGINE_OBJ := $(patsubst $(ENGINE_DIR)/%.cpp, $(BUILD_DIR)/$(ENGINE_NAME)/%.o, $(ENGINE_SRC))
ENGINE_INC := -I$(ENGINE_DIR)
ENGINE_LIB := $(LIB_DIR)/lib$(ENGINE_NAME).a

CXX := g++
CXXFLAGS := -Wall -std=c++17
AR := ar

# La librería depende explícitamente del directorio lib y build/engine
$(ENGINE_LIB): | $(LIB_DIR) $(BUILD_DIR)/$(ENGINE_NAME)
$(ENGINE_LIB): $(ENGINE_OBJ)
	$(AR) rcs $@ $^

$(BUILD_DIR)/$(ENGINE_NAME)/%.o: $(ENGINE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(ENGINE_INC) -c $< -o $@

$(LIB_DIR):
	mkdir -p $@

$(BUILD_DIR)/$(ENGINE_NAME):
	mkdir -p $@

