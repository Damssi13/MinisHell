NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS = -lreadline
RM = rm -f
LIBFT = Libft/libft.a

SRC = minishell.c Parser.c Lexer.c helper_func.c execution.c dms_parser.c \
		node_func.c free_func.c ./builtins/ft_cd.c ./builtins/ft_echo.c \
		./builtins/ft_env.c ./builtins/ft_exit.c ./builtins/ft_export.c \
		./builtins/ft_pwd.c ./builtins/ft_unset.c ./builtins/ft_export_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCompiling minishell..."
	@make -C Libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C Libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C Libft fclean
	@$(RM) $(NAME)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re
