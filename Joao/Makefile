# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: atusveld <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/08 15:54:56 by atusveld      #+#    #+#                  #
#    Updated: 2024/01/26 15:09:40 by jovieira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

SRC			=		Src/main.c\
					Src/Prompt/prompt.c\
					Src/Token/token.c\

DR_SRC		=		Src/
DR_INC		=		Includes/
DR_LIBFT	=		Libft/


LIBFT		=		Libft/libft.a

CFLAGS		=		-Wall -Wextra -Werror
# CFLAGS		+=		-g -fsanitize=address

INC			=		-ILibft/ -IIncludes/
OBJ			=		$(SRC:.c=.o)

CC			=		cc

all:
	@$(MAKE) $(NAME) -j4 --no-print-directory

$(NAME): $(LIBFT) $(OBJ)
	@cc $(OBJ) $(LIBFT) $(CFLAGS) $(INC) $(LFLAGS) -o $(NAME) -lreadline
	@echo "- [COMPILED]"

%.o:		%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C Libft --no-print-directory

clean:
	@rm -f $(OBJ)
	@make clean -C Libft --no-print-directory

fclean:		clean
	@rm -f $(OBJ)
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "- [LIBFT CLEAN]"

re:			fclean all
	@echo "- [REBUILT]"

.PHONY: all clean fclean re
