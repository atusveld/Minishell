/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alex.h                               		        :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//==========[ ALEX_H ]==========//
#ifndef ALEX_H
# define ALEX_H
//==========[ LIBRARIES ]==========//
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include "parse.h"
//==========[ STRUCTS ]==========//

typedef struct s_gen
{
	char	**env_paths;
	char	**cmd_args;
	char	*cmd_path;
	int		e_code;
	t_env	*env;
}	t_gen;

typedef struct s_pipe
{
	int	tube[2];
	int	in_fd;
}	t_pipe;

//==========[ EXECUTION ]==========//
t_pipe	*ft_init_pipes(void);
void	ft_exe(t_parse *parsed, t_gen *gen);
int		ft_fork(void);
int		ft_exe_single(t_gen *gen, t_env *env);
int		ft_exe_multi(t_gen *gen, t_parse *parsed, int status, int cmd_c);
void	ft_exe_first(t_gen *gen, t_pipe *pipe);
void	ft_exe_mid(t_gen *gen, t_pipe *pipe);
void	ft_exe_last(t_gen *gen, t_pipe *pipe);
int		ft_count_cmd(t_parse *parsed);
void	ft_fml(t_gen *gen, t_pipe *pipe, int i, int cmd_c);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
void	ft_e_code(t_gen *gen);
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
char	*get_cmd_path(t_gen *gen);
//==========[ BUILTINS ]==========//
int		ft_if_builtin(t_gen *gen, t_parse *parsed);
void	ft_echo(t_gen *gen);
void	ft_pwd(t_gen *gen);
void	ft_cd(t_gen *gen);
void	ft_cd_update_env(t_gen *gen, char *old_p, char *new_p);
void	ft_env(t_gen *gen);
int		ft_unset(t_env *env, char **argv);
void	ft_unset_env(t_env **env, char *key);
int		ft_export_print(char **env);
int		ft_export(t_gen *gen);
//==========[ REDIRECT ]==========//
void	ft_red_out(t_parse *parsed, t_gen *gen);
void	ft_red_in(t_parse *parsed, t_gen *gen);
int		ft_create_file(t_parse *parsed);
void	ft_write_to_file(int fd, t_parse *parsed);
void	ft_append(t_parse *parsed);
//==========[ AUX ]==========//
void	ft_init(t_parse *parsed, t_gen *gen);
void	*ft_free_arr(char **arr);
void	ft_exit(t_parse *parsed);
void	ft_error(char *str, t_gen *gen);
char	**get_paths(t_gen *gen);
void	ft_free_gen(t_gen *gen);
//==========[  ]==========//
// char	*expandable(char *def, t_env *tmp_env);
// void	found_here(t_parse *data, t_env *env, char *delimiter);

#endif