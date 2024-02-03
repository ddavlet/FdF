CC = cc
NAME = fdf
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
INCLUDES = -I$(LIBFT_DIR) -Iinc -Iinclude
RM = rm -f
RANNAME = ranlib $(NAME)
SRC_DIR = ./src/
SRC_NAME = fdf.c coordinates.c vars.c utils_1.c hooks.c utils_2.c maths.c free.c points.c \
				bresenhams.c draw_utils.c utils_3.c projections.c
SRC := $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ := $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) -g $(OBJ) $(LIBFT) $(INCLUDES) libmlx42.a -ldl -lglfw -pthread -lm -o $(NAME)
#	$(CC) $(FLAGS) -g $(OBJ) $(LIBFT) libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib" -o $(NAME)

%.o: %.c
	$(CC) -g $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) $(BONUS_OBJ)
		$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
		$(RM) $(NAME) $(BONUS)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
