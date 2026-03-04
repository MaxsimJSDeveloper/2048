NAME = endgame
CC = clang

# Шляхи
RAYLIB_DIR = resource/raylib
RAYLIB_A = $(RAYLIB_DIR)/libraylib.a
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# Прапорці
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I$(INC_DIR) -I$(RAYLIB_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Визначення ОС
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    LDFLAGS = $(RAYLIB_A) -lGL -lm -lpthread -ldl -lrt -lX11
endif

ifeq ($(UNAME_S), Darwin)
    LDFLAGS = $(RAYLIB_A) -framework IOKit -framework Cocoa -framework OpenGL
endif

# Додаємо підтримку Windows (через MinGW/MSYS2)
ifneq (,$(findstring NT,$(UNAME_S)))
    NAME = endgame.exe
    LDFLAGS = $(RAYLIB_A) -lgdi32 -lwinmm -lopengl32
endif

all: $(NAME)

$(NAME): $(RAYLIB_A) $(OBJS)
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "SUCCESS: $(NAME) created for $(UNAME_S)."

$(RAYLIB_A):
	@echo "Building Raylib..."
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@echo "Cleaned up."

.PHONY: all clean

