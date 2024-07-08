/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/04/09 12:36:17 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

/*
	IN = <
	OUT = >
	APPEND = >>
	HEREDOC = <<
*/
typedef enum e_type
{
	EMPTY,
	DEFAULT,
	PIPEPIPE,
	PIPE,
	IN,
	OUT,
	APPEND,
	HEREDOC,
	END,
}			t_type;

typedef struct s_data
{
	char			*input;
}	t_data;

typedef struct s_token
{
	char				*content;
	t_type				type;
	int					infile;
	int					operator;
	struct s_token		*next;
}	t_token;

// Token creation Functions
int		asign_token(t_token *token);
t_token	*ft_token(char *s);

// List Functions
int		ft_lstsize(t_token *lst);
void	ft_lstprint(t_token *token);
void	ft_lstclear_mod(t_token **lst);
void	ft_lstdelone_mod(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_front(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew(void *content);

#endif
