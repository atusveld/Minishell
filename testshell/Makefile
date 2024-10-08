# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: atusveld <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2022/12/08 15:54:56 by atusveld      #+#    #+#                  #
#    Updated: 2024/08/22 13:41:32 by jovieira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell

SRC			=		main.c\
					Src/Token/token.c\
					Src/Token/ft_tokenizer.c\
					Src/Lists/List_token/ft_lstnew.c\
					Src/Lists/List_token/ft_lstadd_back.c\
					Src/Lists/List_token/ft_lstadd_front.c\
					Src/Lists/List_token/ft_lstprint.c\
					Src/Lists/List_token/ft_lstdelone.c\
					Src/Lists/List_token/ft_lstlast.c\
					Src/Lists/List_token/ft_lstclear.c\
					Src/Lists/List_token/ft_lstsize.c\
					Src/Lists/List_parse/ft_redir_new.c\
					Src/Lists/List_parse/ft_add_redir.c\
					Src/Lists/List_parse/ft_redir_del.c\
					Src/Lists/List_parse/ft_redir_last.c\
					Src/Lists/List_parse/ft_redir_clear.c\
					Src/Lexer/syntax.c\
					Src/Lexer/lexer.c\
					Src/Lexer/lexer_err.c\
					Src/Parse/parser.c\
					Src/Lexer/quotes_lexer.c\
					Src/Heredoc/heredoc.c\
					Src/Heredoc/expand.c\
					Src/Heredoc/expansion.c\
					Src/Heredoc/expansion_utils.c\
					Src/Heredoc/heredoc_utils.c\
					Src/Heredoc/signal_utils.c\
					Src/Execution/aux.c\
					Src/Execution/exe.c\
					Src/Execution/init.c\
					Src/Execution/utils.c\
					Src/Execution/cution.c\
					Src/Execution/error.c\
					Src/Execution/redirect.c\
					Src/Builtins/builtins.c\
					Src/Builtins/builtins_util.c\
					Src/Builtins/builtins_unset.c\
					Src/Builtins/builtins_export.c\
					Src/Builtins/builtins_export_util.c\
					Src/Environment/env.c\
					Src/Environment/env_util.c\
					Src/Environment/env_lst.c\

DR_SRC		=		Src/
DR_INC		=		Includes/
DR_LIBFT	=		Libft/


LIBFT		=		Libft/libft.a

CFLAGS		=		-Wall -Wextra -Werror -g
# CFLAGS		+=		-fsanitize=address

INC			=		-ILibft/ -IIncludes/
OBJ			=		$(SRC:.c=.o)

# CC			=		cc
CC			=		clang


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
	@echo "- [SHELL CLEAN]"

re:			fclean all
	@echo "- [REBUILT]"

.PHONY: all clean fclean re
