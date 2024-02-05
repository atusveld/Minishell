/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:15:46 by jovieira      #+#    #+#                 */
/*   Updated: 2024/02/05 15:40:52 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

/*
	IN = <
	OUT = >
	APPEND = >>
*/
typedef enum e_type
{
	EMPTY,
	CMD,
	ARG,
	PIPE,
	IN, // <
	OUT, // >
	APPEND, // >>
	END,
}			e_type;

typedef struct s_token
{
	int				type;
	char			*line;
	char			*input;
	// char			**line_history;
	void			*content;
	struct s_token	*token;
	struct s_token	*next;
}	t_token;

int		asign_token(t_token	*token);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(void *content);
t_token	*ft_lstlast(t_token *lst);

#endif
