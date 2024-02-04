CC = cc
AR = ar rcs
NAME = libft.a
FLAGS = -Wall -Werror -Wextra
OPTION = -c -I
INC_DIR = .
RM = rm -f
RANNAME = ranlib $(NAME)
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
				ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
					ft_putunsnbr_fd.c ft_putnbr_hex_fd.c ft_printf.c ft_get_next_line.c ft_atoi_binar.c
OBJ := $(SRC:%.c=%.o)
SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
					ft_lstmap_bonus.c
OBJ_BONUS :=  $(SRC_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_BONUS)
	@$(AR) $(NAME) $(OBJ) $(OBJ_BONUS)
	@$(RANNAME)

%.o: %.c
	@$(CC) $(FLAGS) $(OPTION) $(INC_DIR) $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# $(CC) $(FLAGS) $(OPTION) $(INC_DIR)
