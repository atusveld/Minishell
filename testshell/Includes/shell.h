/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/22 14:22:49 by jovieira      #+#    #+#                 */
/*   Updated: 2024/08/21 13:58:22 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

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
# include <errno.h>

# define NEAR_TOKEN "minishell: syntax error near unexpected token `"
# define CTRL_D "minishell: warning: here-document delimited by end-of-file (wanted `"
# define CTRL_C ">^C"
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
	int				fd;
	char			*filename;
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
	int		e_code;
}	t_gen;

typedef struct s_pipe
{
	int	tube[2];
	int	in_fd;
}	t_pipe;

typedef struct s_shell
{
	t_data	*input;
	t_token	*token;
	t_parse	*parsed;
	t_env	*env;
	t_gen	*gen;
}	t_shell;

//==========[ PARSING ]==========//
void	ft_add_redir(t_red **lst, t_red *new);
void	ft_add_parse(t_parse **lst, t_parse *new);
void	ft_redir_clean(t_red **lst);
void	ft_redir_del(t_red *lst);
t_red	*ft_redir_last(t_red *lst);
t_red	*ft_redir_new(char *filename, t_type type);
t_parse	*ft_parse_last(t_parse *lst);
void	parse(t_shell *shell);

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
int	found_here(t_shell *shell, t_parse *temp_parse, char *delimiter);

//==========[ EXPANSIONS ]==========//
// char	*expandable(char *def, t_env *tmp_env);
char	*expandable(char *def, t_shell *shell);
char	*remove_quote(char *delimiter, char quote);
char	*remove_quote_unsp(char *delimiter);
char	*end_expand(t_token *token, t_exp *exp_data);
// void	tmp_join(t_exp *exp_data, t_token *token, t_env *tmp_env);
void	tmp_join(t_exp *exp_data, t_shell *shell);
void	token_expand(t_shell *shell);
t_exp	*exp_init(t_exp *exp_data);

//==========[ SIGNALS ]==========//
void	set_signals(void);
void	unset_signals(int sig);
void	ignore_signal(void);

// ==========[ EXECUTION ]==========//
t_pipe	*ft_init_pipes(t_shell *shell, int cmd_count);
int 	ft_init_pipes_pids(t_shell *shell, t_pipe **pipes, int **pids);
void	ft_fork_exe(t_shell *shell, t_parse *parsed, t_pipe *pipes, int *pids, int cmd_c);
void	ft_exe(t_parse *parsed, t_shell *shell);
int		ft_fork(t_shell *shell);
void 	close_pipes(t_pipe *pipes, int cmd_c, int i);
int		ft_exe_single(t_shell *shell, char *path, char **arr);
int 	ft_exe_multi(t_shell *shell, t_parse *parsed, int status);
int		ft_count_cmd(t_parse *parsed);
void 	ft_dup_exe(t_shell *shell, t_pipe *pipes, int i, int cmd_c);
void 	ft_dup_pipes(t_pipe *pipes, int i, int cmd_c);
void 	ft_exec_cmd(t_shell *shell, char *path, char **env_arr);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);

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
char	*get_cmd_path(t_shell *shell);

//==========[ BUILTINS ]==========//
int		ft_if_builtin(t_shell *shell);
int		ft_export_print(char **env);
int		ft_export(t_shell *shell);
int		ft_unset(t_shell *shell, char **argv);
void	ft_echo(t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_cd(t_shell *shell);
void	ft_cd_update_env(t_shell *shell, char *old_p, char *new_p);
void	ft_env(t_shell *shell);

//==========[ REDIRECTION ]==========//
void	ft_red_out(t_shell *shell);
void	ft_red_in(t_shell *shell);
int		ft_red_single(t_shell *shell);
int		ft_create_file(t_shell *shell);
void	ft_write_to_file(int fd, t_shell *shell);
void	ft_append(t_shell *shell);

//==========[ AUX ]==========//
t_shell	*init_shell(char **envp, t_shell *shell);
void	*ft_free_arr(char **arr);
void	ft_exit(t_shell *shell);
void	ft_error(char *str, t_shell *shell, int e_code);
void	ft_error_ne(char *str, t_shell *shell, int e_code);
char	**get_paths(t_shell *shell);
void	ft_free_gen(t_shell *shell);

//==========[  ]==========//

void	print_env(t_shell	*shell);

#endif
