/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                               		        :+:    :+:            */
/*                                                     +:+                    */
/*   By: atusveld <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 15:26:55 by atusveld      #+#    #+#                 */
/*   Updated: 2022/09/07 17:40:34 by atusveld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//==========[ ENV_H ]==========//
#ifndef ENV_H
#define ENV_H
//==========[ LIBRARIES ]==========//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "token.h"
#include "parse.h"
#include "lexer.h"
#include "exec.h"
//==========[ STRUCTS ]==========//
typedef	struct s_env
{
	struct s_env	*next;
	char				*str;
	char				*key;
	char				*val;
}	t_env;

//==========[ PROTOTYPES ]==========//
char	**get_paths(t_gen *gen);
char	*get_cmd_path(t_gen *gen);
// t_env	*ft_init_env(char **envp);
// t_env	*ft_env_cpy(t_env *env);

#endif