OS := $(shell uname -s)

CXX := gcc
CXXFLAGS := -Wall -Wextra

ifeq ($(OS),Linux)
    EXE := Main_Program
else ifeq ($(OS),Darwin)  # macOS
    EXE := Main_Program
else ifeq ($(OS),Windows_NT)
    EXE := Main_Program.exe
    CXXFLAGS += -DWIN32
endif

SRC_DIRS := . 1_User 2_Libralian 3_Function
OBJ_DIR := obj

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(EXE)

$(EXE): $(OBJS)
    $(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
    @mkdir -p $(dir $@)
    $(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
    rm -rf $(OBJ_DIR) $(EXE)

run: all
    @./$(EXE)
    @$(MAKE) clean

.PHONY: all clean run