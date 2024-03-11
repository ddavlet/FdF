CC = cc
NAME = fdf
FLAGS = -Wall -Werror -Wextra -g
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBMLX = ./MLX42
INCLUDES = -I$(LIBFT_DIR) -Iinc -I$(LIBMLX)/include
RM = rm -f
RANNAME = ranlib $(NAME)
SRC_DIR = ./src/
SRC_NAME = fdf.c coordinates.c vars.c utils_1.c hooks.c utils_2.c maths.c free.c points.c \
				bresenhams.c draw_utils.c utils_3.c projections.c
SRC := $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ := $(SRC:.c=.o)
TEST := ./test
DRAW := ./draw

all: libmlx draw $(NAME)

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_DIR)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then\
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX);\
		cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1 && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1;\
		mv $(LIBMLX)/include/MLX42/MLX42_Int.h $(LIBMLX)/include/MLX42_Int.h;\
	fi

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDES) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -o $(NAME)
#	$(CC) $(FLAGS) -g $(OBJ) $(LIBFT) libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib" -o $(NAME)
	@bash makedraw.sh

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(LIBMLX)
	@$(RM) -r $(TEST)
	@$(RM) ./test.sh
	@$(RM) -r $(DRAW)
	@$(RM) ./makedraw.sh

re: fclean all

test:
	@if [ ! -d "$(TEST)" ]; then\
		git clone git@github.com:ddavlet/FdF_test.git $(TEST);\
		mv $(TEST)/test.sh ./test.sh;\
	fi

draw:
	@if [ ! -d "$(DRAW)" ]; then\
		git clone git@github.com:ddavlet/draw.git $(DRAW);\
		mv $(DRAW)/makedraw.sh ./makedraw.sh;\
	fi

.PHONY: all clean fclean re test draw
