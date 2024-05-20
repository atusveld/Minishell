/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:56 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/06 15:08:45 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"

typedef	struct s_red
{
	int				fd; // return from function open, after close file
	char			*filename; // </>/<< + arg // <<???
	t_type			type;
	struct s_red	*next;
}			t_red;

typedef struct s_parse
{
	char			**argv;
	t_red			*redir_in;
	t_red			*redir_out;
	struct s_parse	*next;
}	t_parse;


// Main Parse Function
t_parse	*parse(t_token *token);

// Heredoc
void	found_here(t_token	*token);

// Parse List Functions
void	ft_add_redir(t_red **lst, t_red *new);
void	ft_redir_clean(t_red **lst);
void	ft_redir_del(t_red *lst);
t_red	*ft_redir_last(t_red *lst);
t_red	*ft_redir_new(char *filename, t_type type);

#endif