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
#define ALEX_H
//==========[ LIBRARIES ]==========//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "token.h"
#include "parse.h"
#include "lexer.h"
//==========[ STRUCTS ]==========//
typedef	struct s_env
{
	struct s_env	*next;
	char				*str;
	char				*key;
	char				*val;
}	t_env;

typedef	struct s_gen
{
	char	**env_paths;
	char	**cmd_args;
	char	*cmd_path;
	t_env	*env;
}	t_gen;

typedef struct s_pipe
{
	int	tube[2];
	int	in_fd;
	int	*pid;
	int	i;
}	t_pipe;
//==========[ PROTOTYPES ]==========//
int		new_process(t_gen *gen, char **envp);
int		ft_if_builtin(t_gen *gen);
void	ft_cd_update_env(t_gen *gen, char *old_p, char *new_p);
void	ft_add_envtry(t_env *env, char *key, char *val);
void	ft_env_add_front(t_env **env, t_env *new);
void	ft_free_env_ele(t_env *env);
void	ft_free_env(t_env **env);
void	ft_init(t_parse *parsed, t_gen *gen);
void	ft_error(char *str);
void	ft_echo(char **arr);
void	ft_env(t_gen *gen);
void	ft_cd(t_gen *gen);
void	ft_exit(void);
void	ft_pwd(void);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
char	**ft_env_back_to_array(t_env *env);
char	*ft_get_env(t_env *env, char *key);
char	*get_cmd_path(t_gen *gen);
char	**get_paths(t_gen *gen);
t_env	*ft_find_env(t_env *env, char *key);
t_env	*ft_new_envtry(char *envp);
t_env	*ft_build_env(char **envp);

#endif