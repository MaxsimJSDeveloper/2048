NAME = endgame
CC = clang

RAYLIB_DIR = resource/raylib
RAYLIB_A = $(RAYLIB_DIR)/libraylib.a
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR) -I$(RAYLIB_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    RM = rm -rf
    NAME_BIN = $(NAME).exe
    LDFLAGS = $(RAYLIB_A) -lgdi32 -lwinmm -lopengl32
else
    RM = rm -rf
    NAME_BIN = $(NAME)
    ifeq ($(UNAME_S), Linux)
        LDFLAGS = $(RAYLIB_A) -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(UNAME_S), Darwin)
        LDFLAGS = $(RAYLIB_A) -framework IOKit -framework Cocoa -framework OpenGL
    endif
endif

all: $(NAME_BIN)

$(NAME_BIN): $(RAYLIB_A) $(OBJS)
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "SUCCESS: $(NAME_BIN) created for $(UNAME_S)."

$(RAYLIB_A):
	@echo "Building Raylib from source..."
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ_DIR) $(NAME) $(NAME).exe
	@echo "Cleaned up objects and binary."

.PHONY: all clean

