/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/22 14:22:49 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/08 17:35:32 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// # include "main.h"
// # include "main.h"
// # include "main.h"
// # include "main.h"

# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
// # include "main.h"

# define NEAR_TOKEN "minishell: syntax error near unexpected token `"
# define ECHOCTL 1000

//==========[ TOKEN STRUCTS ]==========//

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
	char				*cont;
	t_type				type;
	int					infile;
	int					operator;
	struct s_token		*next;
}	t_token;

//==========[ PARSING STRUCTS ]==========//

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
}	t_env;

typedef struct s_exp
{
	int		i;
	bool	in_quotes;
	char	*tmp_str;
	char	*tmp_exp;
}	t_exp;

//==========[ EXE STRUCTS ]==========//

typedef struct s_gen
{
	char	**env_paths;
	char	**cmd_args;
	char	*cmd_path;
	char	*owd;
	int		e_code;
	// t_env	*env;
}	t_gen;

typedef struct s_pipe
{
	int	tube[2];
	int	in_fd;
}	t_pipe;

typedef struct s_main
{
	t_data	*input;
	t_token	*token;
	t_parse	*parsed;
	t_env	*env;
	t_gen	*gen;
}	t_main;

//==========[ PARSING ]==========//
void	ft_add_redir(t_red **lst, t_red *new);
void	ft_add_parse(t_parse **lst, t_parse *new);
void	ft_redir_clean(t_red **lst);
void	ft_redir_del(t_red *lst);
t_red	*ft_redir_last(t_red *lst);
t_red	*ft_redir_new(char *filename, t_type type);
t_parse	*ft_parse_last(t_parse *lst);
t_parse	*parse(t_token *token, t_env *env);

// ==========[ LEXING ]==========//
int		lexer(t_token	*token);
void	lexer_error(int error, char *word);
void	valid_operator(t_token *temp);
void	redirect_check(t_token *temp);
bool	check_double(t_token *temp);
bool	exit_cond_valid(t_token *temp);
bool	single_char_check(t_token *temp);

//==========[ TOKENIZE ]==========//
int		asign_token(t_token *token);
int		ft_lstsize(t_token *lst);
void	ft_lstprint(t_token *token);
void	ft_lstclear_mod(t_token **lst);
void	ft_lstdelone_mod(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstadd_front(t_token **lst, t_token *new);
t_token	*ft_token(char *s);
t_token	*ft_lstnew(void *content);
t_token	*ft_lstlast(t_token *lst);

//==========[ HEREDOC ]==========//
void	found_here(t_parse *data, t_env *env, char *delimiter);

//==========[ EXPANSIONS ]==========//
char	*expandable(char *def, t_env *tmp_env);
char	*remove_quote(char *delimiter, char quote);
char	*remove_quote_unsp(char *delimiter);
char	*end_expand(t_token *token, t_exp *exp_data);
void	tmp_join(t_exp *exp_data, t_token *token, t_env *tmp_env);
void	token_expand(t_token *token, t_env *tmp_env);
t_exp	*exp_init(t_exp *exp_data);

//==========[ SIGNALS ]==========//
void	set_signals(void);
void	unset_signals(void);
void	ignore_signal(void);
void	signal_ctrl_c(int sig);

// ==========[ EXECUTION ]==========//
t_pipe	*ft_init_pipes(void);
void	ft_exe(t_parse *parsed, t_main *main);
int		ft_fork(void);
int		ft_exe_single(t_main *main, t_env *env);
int		ft_exe_multi(t_main *main, t_parse *parsed, int status, int cmd_c);
void	ft_exe_first(t_main *main, t_pipe *pipe);
void	ft_exe_mid(t_main *main, t_pipe *pipe);
void	ft_exe_last(t_main *main, t_pipe *pipe);
int		ft_count_cmd(t_parse *parsed);
void	ft_fml(t_main *main, t_pipe *pipe, int i, int cmd_c);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	ft_e_code(t_main *main);

//==========[ ENVIRONMENT ]==========//
t_env	*ft_find_env(t_env *env, char *key);
t_env	*ft_build_env(char **envp);
t_env	*ft_new_envtry(char *envp);
char	*ft_get_env(t_env *env, char *key);
char	**ft_env_to_array(t_env *env);
void	ft_add_envtry(t_env *env, char *key, char *val);
void	ft_env_add_front(t_env **env, t_env *new);
void	ft_free_env_ele(t_env *env);
void	ft_free_env(t_env **env);
void	ft_del_env(t_env **env, t_env *temp);
char	*get_cmd_path(t_main *main);

//==========[ BUILTINS ]==========//
int		ft_if_builtin(t_main *main, t_parse *parsed);
int		ft_export_print(char **env);
int		ft_export(t_main *main);
int		ft_unset(t_env *env, char **argv);
void	ft_echo(t_main *main);
void	ft_pwd(t_main *main);
void	ft_cd(t_main *main);
void	ft_cd_update_env(t_main *main, char *old_p, char *new_p);
void	ft_env(t_main *main);

//==========[ REDIRECTION ]==========//
void	ft_red_out(t_parse *parsed, t_main *main);
void	ft_red_in(t_parse *parsed, t_main *main);
int		ft_create_file(t_parse *parsed);
void	ft_write_to_file(int fd, t_parse *parsed);
void	ft_append(t_parse *parsed);

//==========[ AUX ]==========//
t_main	*init_main(char **envp, t_main *main);
void	*ft_free_arr(char **arr);
void	ft_exit(t_parse *parsed);
void	ft_error(char *str, t_main *main);
char	**get_paths(t_main *main);
void	ft_free_gen(t_main *main);

//==========[  ]==========//
// char	*expandable(char *def, t_env *tmp_env);
// void	found_here(t_parse *data, t_env *env, char *delimiter);

#endif
