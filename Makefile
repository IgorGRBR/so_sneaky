NAME=so_long

UNAME=$(shell uname)

CFLAGS=-Wall -Wextra -Werror
CFLAGS_DEBUG = $(CFLAGS) -fsanitize=address -fsanitize=undefined
ifeq ($(UNAME),Linux)
	LFLAGS = -lm -L/usr/lib -lXext -lX11 -lm -lz -L/usr/lib
	MLX_PATH = mlxl/
	# MLX_PATH = mlxl/includes/
	MLX_LIB = $(MLX_PATH)libmlx.a
	# MLX_LIB = mlxl/libmlx.a
	EXT_INCLUDE = /usr/include
	EXT_DEFINES = -D LINUX
	CC = clang
else
	LFLAGS = -lm -Lmlx -lmlx -framework OpenGL -framework AppKit
	# LFLAGS = -framework OpenGL -framework AppKit
	MLX_PATH = mlx/
	MLX_LIB = ""
	EXT_INCLUDE = ""
	EXT_DEFINES = -D OSX
	CC = gcc
endif
SRC_DIR = src
OBJ_DIR = obj
YLIB_PATH = ylib/
YLIB_OBJ = $(wildcard $(addsuffix *.o, $(YLIB_PATH)obj/))
YLIB_DBG_OBJ = $(wildcard $(addsuffix *.o, $(YLIB_PATH)dobj/))
YLIB_LIB = $(YLIB_PATH)ylib.a
DBG_OBJ_DIR = dobj
SRC = $(wildcard $(addsuffix *.c, src/))
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
DBG_OBJ = $(patsubst src/%.c, dobj/%.o, $(SRC))
DEFINES = -D GNL_BSIZE=24 -D LIST_C_STEP=20 $(EXT_DEFINES)
INC_DIR = -I ./ -I $(YLIB_PATH) -I $(MLX_PATH) -I $(EXT_INCLUDE)
AR = ar -rc

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(DBG_OBJ_DIR):
	@mkdir -p $(DBG_OBJ_DIR)

$(NAME): ylib mlx $(OBJ)
	@echo $(NAME): creating binary $(NAME) for platform $(UNAME)
	$(CC) -o $(NAME) $(LFLAGS) $(OBJ) $(YLIB_LIB) $(MLX_LIB)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo $(NAME): building $@
	@$(CC) $(CFLAGS) $(INC_DIR) $(DEFINES) -O3 -c $< -o $@

debug: ylib-debug mlx $(DBG_OBJ)
	@echo $(NAME): creating debuggable binary $(NAME) for platform $(UNAME)
	@$(CC) -o $(NAME) $(LFLAGS) $(DBG_OBJ) $(YLIB_LIB) $(MLX_LIB)

$(DBG_OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(DBG_OBJ_DIR)
	@echo $(NAME): debug building $@
	@$(CC) $(CFLAGS) $(INC_DIR) $(DEFINES) -c $< -o $@ -g

ylib:
	make -C $(YLIB_PATH) ylib

ylib-debug:
	make -C $(YLIB_PATH) debug

ylib-clean:
	make -C $(YLIB_PATH) clean

ylib-fclean:
	make -C $(YLIB_PATH) fclean

mlx:
	make -C $(MLX_PATH) || true
	@echo ""

mlx-clean:
	make -C $(MLX_PATH) clean || true
	@echo ""

clean: ylib-clean mlx-clean
	@echo $(NAME): cleaning objects
	@rm -f $(OBJ) $(DBG_OBJ)

fclean: clean ylib-fclean mlx-clean
	@echo $(NAME): cleaning build artifacts
	@rm -f $(NAME)

re: fclean all

redb: fclean debug

.PHONY: all clean fclean re debug redb ylib ylib-debug ylib-clean ylib-fclean mlxl mlx
