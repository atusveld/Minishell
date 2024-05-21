/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:56 by jovieira      #+#    #+#                 */
/*   Updated: 2024/05/21 17:09:57 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lexer.h"

# define ECHOCTL 1000

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

typedef struct s_here
{
	
}	t_here;

// Main Parse Function
t_parse	*parse(t_token *token);

// Heredoc
void	found_here(t_parse *data, char *delimiter);

// Expantion
// void	expandable(t_token *token, t_env *tmp_env);

// Signal handler

void	set_signals(void);
void	unset_signals(void);
void	ignore_signal(void);
void	signal_ctrl_c(int sig);

// Parse List Functions
void	ft_add_redir(t_red **lst, t_red *new);
void	ft_redir_clean(t_red **lst);
void	ft_redir_del(t_red *lst);
t_red	*ft_redir_last(t_red *lst);
t_red	*ft_redir_new(char *filename, t_type type);

#endif