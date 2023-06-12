TARGET_EXEC ?= game

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src 
INCLUDE_DIRS ?= ./include /usr/include/SDL2 /usr/include/glm

CXX = g++

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJS := $(SRCS:$(SRC_DIRS)/%.cpp=$(BUILD_DIR)/%.o)

INC_FLAGS := $(addprefix -I ,$(INCLUDE_DIRS))

CPPFLAGS ?= $(INC_FLAGS) --std=c++17 -MMD -MP -pthread -w -g 
LDLIBS ?= -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


all: $(TARGET_EXEC) 

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CPPFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)
	rm $(TARGET_EXEC)

MKDIR_P ?= mkdir -p
