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

# สร้างรายชื่อไฟล์ .c (จากทุกโฟลเดอร์)
SRCS := $(wildcard *.c) $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# สร้างรายชื่อไฟล์ .o ใน obj/ ให้ตรงกับที่มา
OBJS := $(foreach src,$(SRCS),$(OBJ_DIR)/$(src:.c=.o))

# ให้ Makefile หาไฟล์ .c ในทุกโฟลเดอร์
vpath %.c $(SRC_DIRS) .

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule สำหรับแปลง c -> o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(OBJS:.o=.d)

clean:
	rm -rf $(OBJ_DIR) $(EXE)

.PHONY: all clean