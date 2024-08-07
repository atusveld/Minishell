/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   .main.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:16:56 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:37 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "main.h"

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

typedef	struct s_env
{
	struct s_env	*next;
	char				*str;
	char				*key;
	char				*val;
	// int					e_code;
}	t_env;

typedef struct s_exp
{
	int		i;
	bool	in_quotes;
	char	*tmp_str;
	char	*tmp_exp;
}	t_exp;

// Main Parse Function
t_parse	*parse(t_token *token, t_env *env);

// Heredoc
void	found_here(t_parse *data, t_env *env, char *delimiter);

// Expantion
char	*expandable(char *def, t_env *tmp_env);
void	token_expand(t_token *token, t_env *tmp_env);
char	*remove_quote(char *delimiter, char quote);
char	*remove_quote_unsp(char *delimiter);
char	*end_expand(char *token, t_exp *exp_data);
t_exp	*exp_init(t_exp *exp_data);
void	tmp_join(t_exp *exp_data, t_token *token, t_env *tmp_env, int action);

// Signal handler

void	set_signals(void);
void	unset_signals(void);
void	ignore_signal(void);
void	signal_ctrl_c(int sig);

// Parse List Functions
void	ft_add_redir(t_red **lst, t_red *new);
void	ft_add_parse(t_parse **lst, t_parse *new);
void	ft_redir_clean(t_red **lst);
void	ft_redir_del(t_red *lst);
t_red	*ft_redir_last(t_red *lst);
t_parse	*ft_parse_last(t_parse *lst);
t_red	*ft_redir_new(char *filename, t_type type);

#endif