CC = cc
NAME = fdf
FLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
INCLUDES = -I $(LIBFT_DIR) -I .
RM = rm -f
RANNAME = ranlib $(NAME)
UTILS_DIR = ./utils/
SRC = fdf.c $(UTILS_DIR)colors.c $(UTILS_DIR)coordinates.c $(UTILS_DIR)vars.c $(UTILS_DIR)utils_1.c $(UTILS_DIR)hooks.c \
			$(UTILS_DIR)utils_2.c $(UTILS_DIR)maths.c
OBJ := $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
#$(CC) $(FLAGS) -g $(OBJ) $(LIBFT) libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	$(CC) $(FLAGS) -g $(OBJ) $(LIBFT) libmlx42.a -Iinclude -lglfw -L"./glfw/3.3.9/lib" -o $(NAME)

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
