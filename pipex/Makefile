NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iincludes

MANDATORY_SRCS = \
	mandatory/main.c \
	mandatory/pipex.c \
	mandatory/get_path.c \
	mandatory/utils.c

BONUS_SRCS = \
	bonus/main_bonus.c \
	bonus/pipex_bonus.c \
	bonus/get_path_bonus.c \
	bonus/utils_bonus.c

# Compilação da parte obrigatória
all:
	$(CC) $(CFLAGS) $(INC) $(MANDATORY_SRCS) -o $(NAME)

# Compilação da parte bônus
bonus:
	$(CC) $(CFLAGS) $(INC) $(BONUS_SRCS) -o $(NAME)

clean:
	@echo "Nada para limpar (sem ficheiros .o gerados)."

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
